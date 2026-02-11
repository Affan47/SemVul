SetCoefficients(double a[10])
{
  int i;
  double *c=this->Coefficients;

  for (i=0; i < 10; i++ )
    {
    if ( a[i] != c[i] )
      {
      break;
      }
    }

  if ( i < 10 )
    {
    this->Modified();
    for (i=0; i < 10; i++ )
      {
      c[i] = a[i];
      }
    }
}
