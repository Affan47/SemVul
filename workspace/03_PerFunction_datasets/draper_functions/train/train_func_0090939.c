clutter_ease_in_out_elastic (double t,
                             double d)
{
  double p = d * (.3 * 1.5);
  double s = p / 4;
  double q = t / (d / 2);

  if (q == 2)
    return 1.0;

  if (q < 1)
    {
      q -= 1;

      return -.5 * (pow (2, 10 * q) * sin ((q * d - s) * (2 * G_PI) / p));
    }
  else
    {
      q -= 1;

      return pow (2, -10 * q)
           * sin ((q * d - s) * (2 * G_PI) / p)
           * .5 + 1.0;
    }
}
