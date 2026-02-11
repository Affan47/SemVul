get_token(FILE *fp,
          char *buf,
	  int  buflen,
	  int  *linenum)
{
  int	ch,
	quote;
  char	*bufptr,
	*bufend;


  for (;;)
  {


    while (isspace(ch = getc(fp)))
    {
      if (ch == '\n')
        (*linenum) ++;
    }


    if (ch == EOF)
      return (NULL);
    else if (ch == '\'' || ch == '\"')
    {


      quote  = ch;
      bufptr = buf;
      bufend = buf + buflen - 1;

      while ((ch = getc(fp)) != EOF)
      {
        if (ch == '\\')
	{


	  if (bufptr < bufend)
	    *bufptr++ = ch;

	  if ((ch = getc(fp)) != EOF && bufptr < bufend)
	    *bufptr++ = ch;
	}
	else if (ch == quote)
          break;
	else if (bufptr < bufend)
          *bufptr++ = ch;
      }

      *bufptr = '\0';

      return (buf);
    }
    else if (ch == '#')
    {


      while ((ch = getc(fp)) != EOF)
	if (ch == '\n')
          break;

      (*linenum) ++;
    }
    else
    {


      ungetc(ch, fp);

      bufptr = buf;
      bufend = buf + buflen - 1;

      while ((ch = getc(fp)) != EOF)
	if (isspace(ch) || ch == '#')
          break;
	else if (bufptr < bufend)
          *bufptr++ = ch;

      if (ch == '#')
        ungetc(ch, fp);
      else if (ch == '\n')
        (*linenum) ++;

      *bufptr = '\0';

      return (buf);
    }
  }
}
