adjust_hue(const double *hue_map, double hue, size_t points)
{
  if (hue_map)
    {
      hue += interpolate_value(hue_map, hue * points / 6.0);
      if (hue < 0.0)
	hue += 6.0;
      else if (hue >= 6.0)
	hue -= 6.0;
    }
  return hue;
}
