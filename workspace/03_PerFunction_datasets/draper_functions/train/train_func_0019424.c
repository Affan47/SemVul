get_string(char   **src,
           char   *dst,
	   size_t dstsize)
{
  char	*srcptr,
	*dstptr,
	*dstend,
	quote;


  srcptr = *src;
  dstptr = dst;
  dstend = dst + dstsize - 1;

  *dstptr = '\0';


  while (isspace(*srcptr & 255))
    srcptr ++;

  if (!*srcptr)
  {
    *src = srcptr;

    return (NULL);
  }


  while (*srcptr && !isspace(*srcptr & 255))
  {
    if (*srcptr == '\\')
    {
      srcptr ++;

      if (!*srcptr)
      {
        fputs("epm: Expected character after backslash!\n", stderr);

        *src = srcptr;
        *dst = '\0';

	return (NULL);
      }
    }
    else if (*srcptr == '\'' || *srcptr == '\"')
    {


      quote = *srcptr++;

      while (*srcptr != quote && *srcptr)
      {
        if (*srcptr == '\\')
	{
	  srcptr ++;

	  if (!*srcptr)
	  {
            fputs("epm: Expected character after backslash!\n", stderr);

            *src = srcptr;
            *dst = '\0';

	    return (NULL);
	  }
	}

	if (dstptr < dstend)
	  *dstptr++ = *srcptr;

	srcptr ++;
      }

      if (!*srcptr)
      {
        fprintf(stderr, "epm: Expected end quote %c!\n", quote);

        *src = srcptr;
	*dst = '\0';

	return (NULL);
      }

      srcptr ++;
      continue;
    }

    if (dstptr < dstend)
      *dstptr++ = *srcptr;

    srcptr ++;
  }

  *dstptr = '\0';


  while (isspace(*srcptr & 255))
    srcptr ++;


  *src = srcptr;

  return (dst);
}
