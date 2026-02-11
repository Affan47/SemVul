xml_escape(const char *s)
{
  char		*e,
		*eptr;
  const char	*sptr;
  size_t	bytes;


  for (bytes = 0, sptr = s; *sptr; sptr ++)
    if (*sptr == '&')
      bytes += 4;
    else if (*sptr == '<' || *sptr == '>')
      bytes += 3;


  if (bytes == 0)
    return (strdup(s));


  if ((e = malloc(bytes + 1 + strlen(s))) == NULL)
    return (NULL);

  for (eptr = e, sptr = s; *sptr; sptr ++)
    if (*sptr == '&')
    {
      *eptr++ = '&';
      *eptr++ = 'a';
      *eptr++ = 'm';
      *eptr++ = 'p';
      *eptr++ = ';';
    }
    else if (*sptr == '<')
    {
      *eptr++ = '&';
      *eptr++ = 'l';
      *eptr++ = 't';
      *eptr++ = ';';
    }
    else if (*sptr == '>')
    {
      *eptr++ = '&';
      *eptr++ = 'g';
      *eptr++ = 't';
      *eptr++ = ';';
    }
    else
      *eptr++ = *sptr;

  *eptr = '\0';

  return (e);
}
