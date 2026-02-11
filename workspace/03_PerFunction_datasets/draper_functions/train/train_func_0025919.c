abbreviate(const char *s,
           char       *buf,
	   int        bufsize)
{
  char	*bufptr;


  for (bufptr = buf, bufsize -= 4; *s && bufsize > 0; s ++)
  {
    if (*s == '\n')
    {
      if (bufsize < 2)
        break;

      *bufptr++ = '\\';
      *bufptr++ = 'n';
      bufsize -= 2;
    }
    else if (*s == '\t')
    {
      if (bufsize < 2)
        break;

      *bufptr++ = '\\';
      *bufptr++ = 't';
      bufsize -= 2;
    }
    else if (*s >= 0 && *s < ' ')
    {
      if (bufsize < 4)
        break;

      sprintf(bufptr, "\\%03o", *s);
      bufptr += 4;
      bufsize -= 4;
    }
    else
    {
      *bufptr++ = *s;
      bufsize --;
    }
  }

  if (*s)
    memcpy(bufptr, "...", 4);
  else
    *bufptr = '\0';

  return (buf);
}
