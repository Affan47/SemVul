print_error_msg(const char *format, ...)
{
  va_list   arg;

  if (!error_file) error_file = stderr;

  va_start(arg, format);
  vfprintf(error_file, format, arg);
  va_end(arg);

  return 0;
}
