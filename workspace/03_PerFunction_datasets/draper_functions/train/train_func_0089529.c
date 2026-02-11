sinksuck(int sock, int len)
{
  char sink[512];
  int nread;

  do {
    nread = sread(sock, sink, LAM_min(len, 512));
    if (nread <= 0)
      return (nread);

    len -= nread;
  } while (len > 0);

  return (1);
}
