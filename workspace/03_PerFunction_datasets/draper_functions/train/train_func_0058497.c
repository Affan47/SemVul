swe_d2l(double x)
{
  if (x >=0)
    return ((long) (x + 0.5));
  else
    return (- (long) (0.5 - x));
}
