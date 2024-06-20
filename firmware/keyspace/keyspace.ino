#include <Adafruit_NeoPixel.h>

#define NUMPIXELS        1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

//
// run 
// sudo chmod 666 /dev/ttyACM0
// constantly + find a way to make it permanent

// the setup routine runs once when you press reset
void setup() {
  Serial.begin(115200);

#if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // not so bright

  for (int i = 0; i < 6; i++) {
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int x_neg = digitalRead(0);
  int x_pos = digitalRead(1);

  int y_neg = digitalRead(2);
  int y_pos = digitalRead(3);

  int z_neg = digitalRead(4);
  int z_pos = digitalRead(5);

  // Serial.print(x_neg == LOW ? "pressed" : "released");
  uint8_t r = 0x55; // roughly a third due to color perception blending > 0x80
  uint8_t g = 0x55;
  uint8_t b = 0x55;
  
  if (x_neg == LOW) { r -= 0x55; }
  if (x_pos == LOW) { r += 0x9A; }

  if (y_neg == LOW) { g -= 0x55; }
  if (y_pos == LOW) { g += 0x9A; }

  if (z_neg == LOW) { b -= 0x55; }
  if (z_pos == LOW) { b += 0x9A; }

  uint32_t col = (static_cast<uint32_t>(r) << 16) | (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(b);
  pixels.fill(col);
  pixels.show();
  delay(10);
}
