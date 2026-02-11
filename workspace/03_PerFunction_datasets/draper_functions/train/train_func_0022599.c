fz_strlcat(char *dst, const char *src, int siz)
{
	register char *d = dst;
	register const char *s = src;
	register int n = siz;
	int dlen;


	while (*d != '\0' && n-- != 0)
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return dlen + strlen(s);
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return dlen + (s - src);
}
