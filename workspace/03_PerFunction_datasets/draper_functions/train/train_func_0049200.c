angle_diff(double a, double b)
{
  a -= b;
  while( a <= -M_PI ) a += M_2__PI;
  while( a >   M_PI ) a -= M_2__PI;
  if( a < 0.0 ) a = -a;
  return a;
}
