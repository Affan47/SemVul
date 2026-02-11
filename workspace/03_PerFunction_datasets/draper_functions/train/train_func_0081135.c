validate_name(const char *name)
{
  const char	*ptr;


  for (ptr = name; *ptr; ptr ++)
    if (*ptr == '@')
      break;
    else if ((*ptr >= 0 && *ptr <= ' ') || *ptr == 127 || *ptr == '/' ||
             *ptr == '#')
      return (0);


  return ((ptr - name) < 128);
}
