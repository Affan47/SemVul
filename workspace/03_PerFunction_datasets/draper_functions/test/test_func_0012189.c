sigma( float *list, int num, double ln_p_avg)
{
  double val;

  val = variance( list, num, ln_p_avg);
  if (val != 0.0)
    return (sqrt( val));
  else
    return ( 0.0);
}
