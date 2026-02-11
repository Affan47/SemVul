vtkGetDerivativeSequence( double* dP, int p )
{
  int offsetA = 0;
  int offsetB = p+1;

  for ( int i = 1; i <= p; ++ i )
    {
    for ( int j = 0; j <= p - i; ++ j )
      dP[offsetB + j] = static_cast<double>( p - i - j + 1 ) * dP[offsetA + j] / i;

    offsetA = offsetB;
    offsetB += p - i + 1;
    }
}
