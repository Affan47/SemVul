putlong(long n,
        FILE *fp)
{
  if (putc(n >> 24, fp) == EOF)
    return (EOF);
  if (putc(n >> 16, fp) == EOF)
    return (EOF);
  if (putc(n >> 8, fp) == EOF)
    return (EOF);
  if (putc(n, fp) == EOF)
    return (EOF);
  else
    return (0);
}
