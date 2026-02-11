split_dresource(char **st, char **left, char **right)
{
	char *s = *st;
	char *t;
	Boolean quote;


	while (my_isspace(*s))
		s++;


	if (!*s)
		return 0;


	if (*s == ':')
		return -1;


	*left = s;
	for (; *s && *s != ':' && *s != '\n'; s++)
		if (*s == '\\' && *(s+1) == ':')
			s++;
	if (*s != ':')
		return -1;


	for (t = s-1; my_isspace(*t); t--)
		*t = '\0';


	*(s++) = '\0';


	while (*s != '\n' && my_isspace(*s))
		s++;


	if (!*s || *s == '\n')
		return -1;


	*right = s;
	quote = False;
	for (; *s; s++) {
		if (*s == '\\' && *(s+1) == '"')
			s++;
		else if (*s == '"')
			quote = !quote;
		else if (!quote && *s == '\n')
			break;
	}


	if (*s) {
		t = s;
		*st = s+1;
	} else {
		t = s-1;
		*st = s;
	}
	while (my_isspace(*t))
		*t-- = '\0';


	return 1;
}
