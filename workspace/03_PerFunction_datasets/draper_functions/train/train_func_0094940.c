flushbuf(void)
{
  size_t len = gtimo_buflen;
  char * buf = gtimo_buf;

  if (!buf)
	return;

  while (len > 0)
    {
      int r = write(2, buf, len);
      if (r < 0)
	{
	  perror("write");
	  r = len;
	}
      len -= r;
      buf += r;
    }
  gtimo_buflen = 0;
  *gtimo_buf = 0;
}
