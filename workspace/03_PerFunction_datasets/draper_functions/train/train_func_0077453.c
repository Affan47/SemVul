cdk_stream_putc (cdk_stream_t s, int c)
{
  byte buf[2];
  int nwritten;

  if (!s)
    {
      gnutls_assert ();
      return EOF;
    }
  buf[0] = c;
  nwritten = cdk_stream_write (s, buf, 1);
  if (nwritten == EOF)
    return EOF;
  return 0;
}
