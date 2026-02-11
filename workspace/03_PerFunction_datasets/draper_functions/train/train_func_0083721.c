rgb_to_hsv (DATA8 *red, DATA8 *green, DATA8 *blue)
{
  int    r, g, b;
  double h, s, v;
  int    min, max;
  int    delta;

  h = 0.0;

  r = *red;
  g = *green;
  b = *blue;

  if (r > g)
    {
      max = MAX (r, b);
      min = MIN (g, b);
    }
  else
    {
      max = MAX (g, b);
      min = MIN (r, b);
    }

  v = max;

  if (max != 0)
    s = ((max - min) * 255) / (double) max;
  else
    s = 0;

  if (s == 0)
    h = 0;
  else
    {
      delta = max - min;
      if (r == max)
	h = (g - b) / (double) delta;
      else if (g == max)
	h = 2 + (b - r) / (double) delta;
      else if (b == max)
	h = 4 + (r - g) / (double) delta;
      h *= 42.5;

      if (h < 0)
	h += 255;
      if (h > 255)
	h -= 255;
    }

  *red   = h;
  *green = s;
  *blue  = v;
}
