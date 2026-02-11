Malloc(size_t n)
{
  char *s, *r;
  unsigned long *x;
  size_t nn;

  bytes_in_use += n;
  if (bytes_in_use > max_bytes_in_use) {
    max_bytes_in_use = bytes_in_use;
  }

  nn = n + 8;
  s = (char *) malloc(nn);
  x = (unsigned long *) s;
  *x = n;
  r = (void *) (s + 8);

  return r;
}
