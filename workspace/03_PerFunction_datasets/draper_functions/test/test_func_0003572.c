clutter_ease_in_out_cubic (double t,
                           double d)
{
  double p = t / (d / 2);

  if (p < 1)
    return 0.5 * p * p * p;

  p -= 2;

  return 0.5 * (p * p * p + 2);
}
