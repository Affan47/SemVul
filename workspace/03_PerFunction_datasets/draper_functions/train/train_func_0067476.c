vector_scale( double* dest, double c, double* v, int k )
{
  for( --k; k>=0; --k )
    dest[k] = c * v[k];
}
