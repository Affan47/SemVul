getMsgId (const char *p)
{
  const char *q ;
  char *rval ;

  while (*p && isspace((unsigned char) *p)) p++ ;
  while (*p && !isspace((unsigned char) *p)) p++ ;
  while (*p && isspace((unsigned char) *p)) p++ ;

  if ( *p == '\0' )
    return NULL ;

  q = p ;
  while ( *q && !isspace((unsigned char) *q) )
    q++ ;

  rval = xstrndup (p, q - p) ;

  return rval ;
}
