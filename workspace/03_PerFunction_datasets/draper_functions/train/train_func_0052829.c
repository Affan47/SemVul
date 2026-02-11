i18n_printf(const char *format, ...)
{
  char *new_format;
  int return_value;
  va_list args;

  new_format = iconv_from_utf8_to_locale(format, "");

  if(new_format != NULL)
    {
      va_start(args, format);
      return_value = vprintf(new_format, args);
      va_end(args);
      free(new_format);
    }
  else
    return_value = 0;

  return return_value;
}
