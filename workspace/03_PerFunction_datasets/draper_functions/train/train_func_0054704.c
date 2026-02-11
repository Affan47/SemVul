has_whitespace(const char *str)
{
	char c;

	if (str == NULL)
		return (ISC_FALSE);
	while ((c = *str++) != '\0') {
		if (c == ' ' || c == '\t' || c == '\n')
			return (ISC_TRUE);
	}
	return (ISC_FALSE);
}
