solidColorEffect(uint8_t buffer[][3], bool reset)
{
  int i;
  static float brightness=0;

  if (reset) brightness = 0;

  if (brightness<1) brightness += 0.05f;
  else brightness = 1;

  for (i=0; i<NBR_LEDS; i++)
  {
    buffer[i][0] = solidRed*brightness;
    buffer[i][1] = solidGreen*brightness;
    buffer[i][2] = solidBlue*brightness;
  }
}
