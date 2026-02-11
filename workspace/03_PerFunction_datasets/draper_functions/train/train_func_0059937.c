_debug (const char *fmt, va_list ap)
{
  char errbuf[IPMIPOWER_ERROR_BUFLEN];
  int len;

  assert (fmt);

  len = vsnprintf (errbuf, IPMIPOWER_ERROR_BUFLEN, fmt, ap);
  if (power_error_flags & IPMIPOWER_ERROR_STDERR)
    {
      fprintf (stderr, "%s\r\n", errbuf);
      fflush (stderr);
    }
  if (power_error_flags & IPMIPOWER_ERROR_SYSLOG)
    syslog (LOG_DEBUG, "%s", errbuf);
}
