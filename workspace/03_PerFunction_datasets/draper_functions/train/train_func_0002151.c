get_width(const char *fmt, size_t *width)
{
  for (; my_isdigit(&my_charset_latin1, *fmt); fmt++)
  {
    *width= *width * 10 + (uint)(*fmt - '0');
  }
  return fmt;
}
