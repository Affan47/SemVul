get_row_size (A68_TUPLE * tup, int dim)
{
  int span = 1, k;
  for (k = 0; k < dim; k++) {
    int stride = ROW_SIZE (&tup[k]);
    ABEND ((stride > 0 && span > A68_MAX_INT / stride), ERROR_INVALID_SIZE, "get_row_size");
    span *= stride;
  }
  return (span);
}
