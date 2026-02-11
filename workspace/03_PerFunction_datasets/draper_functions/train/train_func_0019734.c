dump_format(const char *name, const char *fmt, ...)
{
  char buf[LARGE_SIZE];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, LARGE_SIZE, fmt, ap);
  va_end(ap);

  print_name(name);
  print_quoted_string(buf);
}
