DecodeQuotedPrintable(char *ptr)
{
	char *s = ptr;
	while (*s != '\0' && *s != '=')
		s++;

	if (*s == '\0')
		return;

	char *d = s;
	do {
		if (*s == '=' && isxdigit(s[1]) && isxdigit(s[2]))
		{
			*d++ = (tohex(s[1]) << 4) | tohex(s[2]);
			s += 3;
		}
		else
		{
			*d++ = *s++;
		}
	} while (*s != '\0');
	*d = '\0';
}
