isprefix(const char *str, const char *prefix, const char **next)
{

	while (*str && *prefix &&
	    tolower((int)*str) == tolower((int)*prefix))
		++str, ++prefix;
	if (*str && *str != ' ')
		return (0);
	if (next) {
		while (*str && *str == ' ')
			++str;
		*next = str;
	}
	return (1);
}
