v900_log(const char *fmt, ...)
{
  va_list ap;

  if (global_opts.debug_level < 1) {
    return;
  }

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
}
