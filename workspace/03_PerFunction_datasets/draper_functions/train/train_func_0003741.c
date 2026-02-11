_gcry_mpi_is_neg (gcry_mpi_t a)
{
  if (a->sign && _gcry_mpi_cmp_ui (a, 0))
    return 1;
  else
    return 0;
}
