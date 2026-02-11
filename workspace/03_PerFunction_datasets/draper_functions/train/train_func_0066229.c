isZero(double x)
{
  if ( x < EPSILON && x > -EPSILON )
    return true;
  else
    return false;
}
