_cdk_free_mpibuf (size_t n, bigint_t * array)
{
  while (n--)
    {
      _gnutls_mpi_release (&array[n]);
    }
}
