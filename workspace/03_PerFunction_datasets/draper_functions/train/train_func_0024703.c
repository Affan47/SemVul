searchchar(s, c)
CONST char *s;
int c;
{
	int wc;

	wc = 0;
	for (;;) {
		if (!*s) return(NULL);

		if (iswcin(s)) {
			s += 2;
			wc = 1;
		}
		else if (iswcout(s)) {
			s += 2;
			wc = 0;
		}
		else if (wc) s++;
		else if (*s == c) break;
		s++;
	}

	return((char *)s);
}
