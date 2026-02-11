mpi2bitstr_nlz (gcry_mpi_t a)
{
  char *p, *buf;
  size_t length = gcry_mpi_get_nbits (a);

  if (!length)
    {
      buf = p = xmalloc (2);
      *p++ = '0';
    }
  else
    {
      buf = p = xmalloc (length + 1);
      while (length-- > 1)
        *p++ = gcry_mpi_test_bit (a, length) ? '1':'0';
      *p++ = gcry_mpi_test_bit (a, 0) ? '1':'0';
    }
  *p = 0;
  return buf;
}
