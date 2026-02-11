xtryvasprintf (const char *fmt, va_list arg_ptr)
{
  int rc;
  char *buf;

  rc = estream_vasprintf (&buf, fmt, arg_ptr);
  if (rc < 0)
    return NULL;
  return buf;
}
