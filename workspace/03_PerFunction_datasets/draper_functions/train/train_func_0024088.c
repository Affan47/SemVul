Aprod2(unsigned int m, unsigned int n, double * x, const double * y ) const
{
  for ( unsigned int col = 0; col < n; col++ )
    {
    double sum = 0.0;

    for ( unsigned int row = 0; row < m; row++ )
      {
      sum += this->A[row][col] * y[row];
      }

    x[col] +=  sum;
    }
}
