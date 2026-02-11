verbprintf(int verb_level, const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  if (verb_level <= verbose_level)
    vfprintf(stdout, fmt, args);
  va_end(args);
}
