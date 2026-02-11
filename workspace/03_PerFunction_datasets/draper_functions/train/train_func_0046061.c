StrTokR(char *str, const char *delim, char **nextp)
{
#if 1


  char *ret;

  if (str == NULL)
    {
    str = *nextp;
    }

  str += strspn(str, delim);

  if (*str == '\0')
    {
    return NULL;
    }

  ret = str;

  str += strcspn(str, delim);

  if (*str)
    {
    *str++ = '\0';
    }

  *nextp = str;

  return ret;
#else
  return strtok_r(str,delim,nextp);
#endif
}
