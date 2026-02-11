ran1()
{
  static double dval = 0.0;
  double rndVal;

  if (dval == 0.0) {
    if( rand()<32768 && rand()<32768 )
      dval =      32768.0;
    else
      dval = 2147483648.0;
  }

  rndVal = (double)rand();
  while( rndVal > dval ) dval *= 2.0;
  return rndVal/dval;
}
