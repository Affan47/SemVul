match
 (struct dtoa_context* C, const char **sp, const char *t)
{
	int c, d;
	CONST char *s = *sp;

	while((d = *t++)) {
		if ((c = *++s) >= 'A' && c <= 'Z')
			c += 'a' - 'A';
		if (c != d)
			return 0;
		}
	*sp = s + 1;
	return 1;
	}
