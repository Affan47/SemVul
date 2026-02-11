parse_numeric_field (struct spec *spec,
                     const char **formatp, bool translated, char *fdi,
                     char **invalid_reason)
{
  const char *format = *formatp;
  char c;

  c = *format;
  if (c >= '0' && c <= '9')
    {
      do
        c = *++format;
      while (c >= '0' && c <= '9');
      *formatp = format;
      return true;
    }
  return false;
}
