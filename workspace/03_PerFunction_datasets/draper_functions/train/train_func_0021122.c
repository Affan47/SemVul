wrap_gcry_mpi_mul_ui (bigint_t w, const bigint_t a, unsigned long b)
{
  if (w == NULL)
    w = _gnutls_mpi_alloc_like (a);

  if (w == NULL)
    return NULL;

  gcry_mpi_mul_ui (w, a, b);

  return w;
}
