memistr (const void *buffer, size_t buflen, const char *sub)
{
  const unsigned char *buf = buffer;
  const unsigned char *t = (const unsigned char *)buffer;
  const unsigned char *s = (const unsigned char *)sub;
  size_t n = buflen;

  for ( ; n ; t++, n-- )
    {
      if ( toupper (*t) == toupper (*s) )
        {
          for ( buf=t++, buflen = n--, s++;
                n && toupper (*t) == toupper (*s); t++, s++, n-- )
            ;
          if (!*s)
            return (const char*)buf;
          t = buf;
          s = (const unsigned char *)sub ;
          n = buflen;
	}
    }
  return NULL;
}
