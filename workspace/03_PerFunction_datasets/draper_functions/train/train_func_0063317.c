strstri(str, sub)
    const char *str;
    const char *sub;
{
    register const char *s1, *s2;
    register int i, k;
# define TABSIZ 0x20
    char tstr[TABSIZ], tsub[TABSIZ];
# if 0
    assert( (TABSIZ & ~(TABSIZ-1)) == TABSIZ );
    assert( &lowc != 0 );
# endif


    if (!*sub)	return (char *) str;


    for (i = 0; i < TABSIZ; i++)  tstr[i] = tsub[i] = 0;
    for (k = 0, s1 = str; *s1; k++)  tstr[*s1++ & (TABSIZ-1)]++;
    for (	s2 = sub; *s2; --k)  tsub[*s2++ & (TABSIZ-1)]++;


    if (k < 0)	return (char *) 0;
    for (i = 0; i < TABSIZ; i++)
	if (tsub[i] > tstr[i])	return (char *) 0;


    for (i = 0; i <= k; i++) {
	s1 = &str[i];
	s2 = sub;
	while (lowc(*s1++) == lowc(*s2++))
	    if (!*s2)  return (char *) &str[i];
    }
    return (char *) 0;
}
