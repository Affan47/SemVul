strip_brackets(char *s)
{
	char *t ;

	if (*s == '(') {
		if ((t = strrchr(++s, ')'))) {
			*t = '\0';
		}
	}

	return s;
}
