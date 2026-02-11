vnote(const char *file, int line, note_level_t level, const char *fmt,
    va_list ap)
{
  int saved_errno = errno;

  note_prefix(file, line, level);
  vfprintf(stderr, fmt, ap);
  fputs("\n", stderr);
#if 0
  fflush(stderr);
#endif
  if (level == NOTE_FATAL) {
    fatality("FATALITY");
  }

  errno = saved_errno;
}
