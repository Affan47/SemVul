intern_char(char *s, char **next)
{
  unsigned char value;

  if (s[0] != '\'' || s[strlen(s)-1] != '\'')
    panic("mal-formed string constant");

  if (s[1] != '\\')
    {
      value = (unsigned)s[1];
      if (s[2] != '\'')
	panic("mal-formed string constant");
      if (next)
	*next = s + 2;
    }
  else
    {

      value = intern_escape(s+2, next);
    }


  value = (signed int)((unsigned char)((unsigned char)((unsigned int)value)));

  if (UCHAR_MAX < value)
    fatal("character constant out of range");

  return value;
}
