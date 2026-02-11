ipmipower_cbuf_printf(cbuf_t cbuf, const char *fmt, ...)
{
  char buf[IPMIPOWER_OUTPUT_BUFLEN];
  va_list ap;
  int written, dropped;
  int len;

  va_start(ap, fmt);


  len = vsnprintf (buf, IPMIPOWER_OUTPUT_BUFLEN, fmt, ap);

  written = cbuf_write (cbuf, buf, len, &dropped);
  if (written < 0)
    {
      IPMIPOWER_ERROR (("cbuf_write: %s", strerror (errno)));
      exit (1);
    }

  va_end(ap);
}
