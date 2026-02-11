isEqualE(double x, double y, double epsilon)
{
  if ( epsilon == 0.0 ) {
    epsilon = EPSILON;
  }

  if ( isZeroE(x-y, epsilon) )
    return true;
  else
    return false;
}
