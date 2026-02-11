test_opaque (void)
{
  gcry_mpi_t a;
  char *p;
  unsigned int nbits;

  p = gcry_xstrdup ("This is a test buffer");
  a = gcry_mpi_set_opaque (NULL, p, 21*8+1);

  if (!gcry_mpi_get_flag (a, GCRYMPI_FLAG_OPAQUE))
    die ("opaque flag not set\n");

  p = gcry_mpi_get_opaque (a, &nbits);
  if (!p)
    die ("gcry_mpi_get_opaque returned NULL\n");
  if (nbits != 21*8+1)
    die ("gcry_mpi_get_opaque returned a changed bit size\n");
  if (strcmp (p, "This is a test buffer"))
    die ("gcry_mpi_get_opaque returned a changed buffer\n");

  if (debug)
    gcry_log_debugmpi ("mpi", a);
  gcry_mpi_release (a);

  p = gcry_xstrdup ("This is a test buffer");
  a = gcry_mpi_set_opaque_copy (NULL, p, 21*8+1);
  gcry_free (p);

  if (!gcry_mpi_get_flag (a, GCRYMPI_FLAG_OPAQUE))
    die ("opaque flag not set\n");

  p = gcry_mpi_get_opaque (a, &nbits);
  if (!p)
    die ("gcry_mpi_get_opaque returned NULL\n");
  if (nbits != 21*8+1)
    die ("gcry_mpi_get_opaque returned a changed bit size\n");
  if (strcmp (p, "This is a test buffer"))
    die ("gcry_mpi_get_opaque returned a changed buffer\n");

  if (debug)
    gcry_log_debugmpi ("mpi", a);

  gcry_mpi_release (a);
}
