clutter_color_from_hls (ClutterColor *color,
			float         hue,
			float         luminance,
			float         saturation)
{
  float tmp1, tmp2;
  float tmp3[3];
  float clr[3];
  int   i;

  hue /= 360.0;

  if (saturation == 0)
    {
      color->red = color->green = color->blue = (luminance * 255);

      return;
    }

  if (luminance <= 0.5)
    tmp2 = luminance * (1.0 + saturation);
  else
    tmp2 = luminance + saturation - (luminance * saturation);

  tmp1 = 2.0 * luminance - tmp2;

  tmp3[0] = hue + 1.0 / 3.0;
  tmp3[1] = hue;
  tmp3[2] = hue - 1.0 / 3.0;

  for (i = 0; i < 3; i++)
    {
      if (tmp3[i] < 0)
        tmp3[i] += 1.0;

      if (tmp3[i] > 1)
        tmp3[i] -= 1.0;

      if (6.0 * tmp3[i] < 1.0)
        clr[i] = tmp1 + (tmp2 - tmp1) * tmp3[i] * 6.0;
      else if (2.0 * tmp3[i] < 1.0)
        clr[i] = tmp2;
      else if (3.0 * tmp3[i] < 2.0)
        clr[i] = (tmp1 + (tmp2 - tmp1) * ((2.0 / 3.0) - tmp3[i]) * 6.0);
      else
        clr[i] = tmp1;
    }

  color->red   = floorf (clr[0] * 255.0 + 0.5);
  color->green = floorf (clr[1] * 255.0 + 0.5);
  color->blue  = floorf (clr[2] * 255.0 + 0.5);
}
