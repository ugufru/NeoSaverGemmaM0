
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 1, NEO_GRB + NEO_KHZ800);
byte hue = 0;
byte offset = 4;
byte offset2 = 3;

void setup()
{
  strip.begin();
  strip.setBrightness(96);
  strip.show();
}

void loop()
{
  doTheRainbowDanceRight();
  delay(100);
}

void doTheRainbowDanceLeft()
{
  pushPixelLeft(Wheel(hue));

  hue = (hue + offset) % 0xFF;

  offset = (offset + offset2) % 0x40;
  offset2 = (offset2 + 1) % 0x20;
}

void doTheRainbowDanceRight()
{
  pushPixelRight(Wheel(hue));

  hue = (hue + offset) % 0xFF;

  offset = (offset + offset2) % 0x40;
  offset2 = (offset2 + 1) % 0x20;
}

void pushPixelLeft(uint32_t color)
{
  uint16_t count = strip.numPixels();

  for (uint16_t i = 0; i < count - 1; i++)
  {
    uint32_t c = strip.getPixelColor(i + 1);
    strip.setPixelColor(i, c);
  }

  strip.setPixelColor(count - 1, color);
  strip.show();
}

void pushPixelRight(uint32_t color)
{
  uint16_t count = strip.numPixels();

  for (uint16_t i = 0; i < count - 1; i++)
  {
    int v = count - i - 1;
    uint32_t c = strip.getPixelColor(v - 1);
    strip.setPixelColor(v, c);
  }

  strip.setPixelColor(0, color);
  strip.show();
}

uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85)
  {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void flashColor(uint32_t color)
{
  for (int x = 0; x < 5; x++)
  {
    for (int i = 0; i < 12; i++)
    {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(50);
    for (int i = 0; i < 12; i++)
    {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(50);
  }
}
