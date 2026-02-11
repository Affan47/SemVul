write_mpi (cdk_stream_t out, bigint_t m)
{
  byte buf[MAX_MPI_BYTES + 2];
  size_t nbits, nread;
  int err;

  if (!out || !m)
    return CDK_Inv_Value;
  nbits = _gnutls_mpi_get_nbits (m);
  if (nbits > MAX_MPI_BITS || nbits < 1)
    return CDK_MPI_Error;

  nread = MAX_MPI_BYTES + 2;
  err = _gnutls_mpi_print_pgp (m, buf, &nread);
  if (err < 0)
    return map_gnutls_error (err);
  return stream_write (out, buf, nread);
}
