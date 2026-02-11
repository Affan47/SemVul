verbosef(int level, const char *fmt, ...) {
  va_list ap;
  if (level > verbosity) return;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
}
