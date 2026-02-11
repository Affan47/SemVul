pwg_unppdize_name(const char *ppd,
		  char       *name,
                  size_t     namesize,
                  const char *dashchars)
{
  char	*ptr,
	*end;


  for (ptr = name, end = name + namesize - 1; *ppd && ptr < end; ppd ++)
  {
    if (_cups_isalnum(*ppd) || *ppd == '-')
      *ptr++ = tolower(*ppd & 255);
    else if (strchr(dashchars, *ppd))
      *ptr++ = '-';
    else
      *ptr++ = *ppd;

    if (!_cups_isupper(*ppd) && _cups_isalnum(*ppd) &&
	_cups_isupper(ppd[1]) && ptr < end)
      *ptr++ = '-';
  }

  *ptr = '\0';
}
