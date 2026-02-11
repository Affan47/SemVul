xasprintf (const char *fmt, ...)
{
  va_list ap;
  char *buf;

  va_start (ap, fmt);
  if (estream_vasprintf (&buf, fmt, ap) < 0)
    log_fatal ("estream_asprintf failed: %s\n", strerror (errno));
  va_end (ap);
  return buf;
}
