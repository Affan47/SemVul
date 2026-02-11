parse_named_field (struct spec *spec,
                   const char **formatp, bool translated, char *fdi,
                   char **invalid_reason)
{
  const char *format = *formatp;
  char c;

  c = *format;
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
    {
      do
        c = *++format;
      while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
             || (c >= '0' && c <= '9'));
      *formatp = format;
      return true;
    }
  return false;
}
