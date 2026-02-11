matvec_mul ARGS5((a,b,c,rows,cols),
REAL **a, REAL *b, REAL *c,
int rows, int cols)
{
  int i,j;

  for ( i = 0 ; i < rows ; i++ )
  { c[i] = 0.0;
    for ( j = 0 ; j < cols ; j++ )
      c[i] += a[i][j]*b[j];
  }
}
