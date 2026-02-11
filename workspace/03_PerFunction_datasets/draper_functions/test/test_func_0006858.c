mpi_buf2bits (gnutls_datum_t * mpi_buf)
{
  bigint_t mpi;
  int rc;

  rc = _gnutls_mpi_scan_nz (&mpi, mpi_buf->data, mpi_buf->size);
  if (rc)
    {
      gnutls_assert ();
      return rc;
    }

  rc = _gnutls_mpi_get_nbits (mpi);
  _gnutls_mpi_release (&mpi);

  return rc;
}
