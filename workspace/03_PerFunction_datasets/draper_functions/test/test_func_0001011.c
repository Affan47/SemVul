get_option_value(const char *list, const char *s)
{
	const char *t;
	size_t n = strlen(s);

	while (list && *list) {
		if (strncmp(list, s, n) == 0) {
			s = t = list + n;
			while (*s && *s != ',')
				s++;
			return xstrndup(t, s-t);
		}
		while (*list && *list++ != ',') ;
	}
	return NULL;
}
