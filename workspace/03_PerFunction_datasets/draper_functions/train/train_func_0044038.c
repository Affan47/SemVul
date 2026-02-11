cupsCharsetToUTF8(
    cups_utf8_t           *dest,
    const char            *src,
    const int             maxout,
    const cups_encoding_t encoding)
{
  cups_utf8_t	*destptr;
#ifdef HAVE_ICONV_H
  size_t	srclen,
		outBytesLeft;
#endif


  DEBUG_printf(("2cupsCharsetToUTF8(dest=%p, src=\"%s\", maxout=%d, encoding=%d)",
	        dest, src, maxout, encoding));

  if (!dest || !src || maxout < 1)
  {
    if (dest)
      *dest = '\0';

    DEBUG_puts("3cupsCharsetToUTF8: Bad arguments, returning -1");
    return (-1);
  }


  if (encoding == CUPS_UTF8 || encoding <= CUPS_US_ASCII ||
      encoding >= CUPS_ENCODING_VBCS_END)
  {
    strlcpy((char *)dest, src, maxout);
    return ((int)strlen((char *)dest));
  }


  destptr = dest;

  if (encoding == CUPS_ISO8859_1)
  {
    int		ch;
    cups_utf8_t	*destend;


    destend = dest + maxout - 2;

    while (*src && destptr < destend)
    {
      ch = *src++ & 255;

      if (ch & 128)
      {
	*destptr++ = 0xc0 | (ch >> 6);
	*destptr++ = 0x80 | (ch & 0x3f);
      }
      else
	*destptr++ = ch;
    }

    *destptr = '\0';

    return ((int)(destptr - dest));
  }


#ifdef HAVE_ICONV_H
  _cupsMutexLock(&map_mutex);

  if (map_encoding != encoding)
  {
    _cupsCharmapFlush();

    map_from_utf8 = iconv_open(_cupsEncodingName(encoding), "UTF-8");
    map_to_utf8   = iconv_open("UTF-8", _cupsEncodingName(encoding));
    map_encoding     = encoding;
  }

  if (map_to_utf8 != (iconv_t)-1)
  {
    char *altdestptr = (char *)dest;

    srclen       = strlen(src);
    outBytesLeft = maxout - 1;

    iconv(map_to_utf8, (char **)&src, &srclen, &altdestptr, &outBytesLeft);
    *altdestptr = '\0';

    _cupsMutexUnlock(&map_mutex);

    return ((int)(altdestptr - (char *)dest));
  }

  _cupsMutexUnlock(&map_mutex);
#endif


  *destptr = '\0';

  return (-1);
}
