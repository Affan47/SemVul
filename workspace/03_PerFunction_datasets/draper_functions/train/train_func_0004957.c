pwg_ppdize_name(const char *ipp,
                char       *name,
		size_t     namesize)
{
  char	*ptr,
	*end;


  *name = toupper(*ipp++);

  for (ptr = name + 1, end = name + namesize - 1; *ipp && ptr < end;)
  {
    if (*ipp == '-' && _cups_isalpha(ipp[1]))
    {
      ipp ++;
      *ptr++ = toupper(*ipp++ & 255);
    }
    else
      *ptr++ = *ipp++;
  }

  *ptr = '\0';
}
