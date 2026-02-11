ruleset_error_real(const char *file, const char *function,
                               int line, enum log_level level,
                               const char *format, ...)
{
  va_list args;

  va_start(args, format);
  vdo_log(file, function, line, FALSE, level, format, args);
  va_end(args);

  if (LOG_FATAL >= level) {
    exit(EXIT_FAILURE);
  }
}
