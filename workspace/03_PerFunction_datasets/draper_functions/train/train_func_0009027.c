print_escaped(const char *s)
{
	if (*s == '\'')
		goto squote;
	do {
		const char *p = strchrnul(s, '\'');

		printf("'%.*s'", (int)(p - s), s);
		if (*p == '\0')
			break;
		s = p;
 squote:

		putchar('"');
		do putchar('\''); while (*++s == '\'');
		putchar('"');
	} while (*s);
}
