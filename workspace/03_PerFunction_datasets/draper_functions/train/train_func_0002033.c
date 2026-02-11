unquote(char *str)
{
	unsigned char *s, *t;

	if (!str)
		return str;

	for (s = (unsigned char *)str; *s != '\0'; s++)
		if (*s == '\\')
			break;
	if (*s == '\0')
		return str;

#define isoctal(c) \
	((c) >= '0' && (c) <= '7')

	t = s;
	do {
		if (*s == '\\' &&
		    isoctal(*(s+1)) && isoctal(*(s+2)) && isoctal(*(s+3))) {
			*t++ = ((*(s+1) - '0') << 6) +
			       ((*(s+2) - '0') << 3) +
			       ((*(s+3) - '0')     );
			s += 3;
		} else
			*t++ = *s;
	} while (*s++ != '\0');

	return str;
}
