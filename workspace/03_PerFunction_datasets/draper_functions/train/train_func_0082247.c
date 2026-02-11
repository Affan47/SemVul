strmove(len, s, spos, d, dpos)
register char *s, *d;
register int len, spos, dpos;
{
    s += spos - 1;
    d += dpos - 1;
    while (*d && --len >= 0)
	*d++ = *s++;
    if (len > 0) {
	while (--len >= 0)
	    *d++ = *s++;
	*d = 0;
    }
}
