xcalloc (size_t n, size_t m)
{
  size_t nbytes;

  nbytes = n * m;
  if (m && nbytes / m != n)
    out_of_core (nbytes, 0);
  return xmalloc_clear (nbytes);
}
