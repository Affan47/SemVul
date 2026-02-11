_gnutls_mpi_scan (bigint_t * ret_mpi, const void *buffer, size_t nbytes)
{
  *ret_mpi =
    _gnutls_mpi_ops.bigint_scan (buffer, nbytes, GNUTLS_MPI_FORMAT_USG);
  if (*ret_mpi == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_MPI_SCAN_FAILED;
    }

  return 0;
}
