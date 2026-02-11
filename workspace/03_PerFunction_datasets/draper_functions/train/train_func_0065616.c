gaussian_random( void )
{
  double x1, x2;
  double r = 0;
  do
  {
    x1 = 2.0 * random() - 1.0;
    x2 = 2.0 * random() - 1.0;

    r = x1*x1 + x2*x2;
  }
  while ( (r >= 1.0) || (r == 0) );

  r = sqrt( (-2.0 * log(r)) / r );

  return x1 * r;
}
