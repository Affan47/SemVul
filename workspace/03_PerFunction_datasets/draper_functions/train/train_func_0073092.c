get_attr(const char *p,
                      const char *n,
		      char       *buf,
		      int        bufsize)
{
  char	name[255],
	*ptr,
	quote;


  buf[0] = '\0';

  while (*p && *p != '>')
  {
    while (isspace((*p)&255))
      p ++;

    if (*p == '>' || !*p)
      return (NULL);

    for (ptr = name; *p && !isspace((*p)&255) && *p != '=' && *p != '>';)
      if (ptr < (name + sizeof(name) - 1))
        *ptr++ = *p++;
      else
        p ++;

    *ptr = '\0';

    if (isspace((*p)&255) || !*p || *p == '>')
      buf[0] = '\0';
    else
    {
      if (*p == '=')
        p ++;

      for (ptr = buf; *p && !isspace((*p)&255) && *p != '>';)
        if (*p == '\'' || *p == '\"')
	{
	  quote = *p++;

	  while (*p && *p != quote)
	    if ((ptr - buf + 1) < bufsize)
	      *ptr++ = *p++;
	    else
	      p ++;

          if (*p == quote)
	    p ++;
	}
	else if ((ptr - buf + 1) < bufsize)
	  *ptr++ = *p++;
	else
	  p ++;

      *ptr = '\0';
    }

    if (strcasecmp(n, name) == 0)
      return (buf);
    else
      buf[0] = '\0';

    if (*p == '>')
      return (NULL);
  }

  return (NULL);
}
