isnumeric(s)
CONST char *s;
{
	int i, n;

	i = 0;
	if ((n = getnum(s, &i)) < 0) return(-1);
#ifndef	BASHSTYLE

	if (s[i]) return(-1);
#endif

	return(n);
}
