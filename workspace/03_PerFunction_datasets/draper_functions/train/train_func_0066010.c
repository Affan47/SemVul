optstring(s, p_str, printopt, validchars)
	char *s;
	char **p_str;
	char *printopt;
	char *validchars;
{
	register char *p;
	register char *out;

	if (*s == '\0')
	{
		nostring(printopt);
		return (NULL);
	}

	*p_str = (char *) ecalloc(strlen(s)+1, sizeof(char));
	out = *p_str;

	for (p = s;  *p != '\0';  p++)
	{
		if (opt_use_backslash && *p == '\\' && p[1] != '\0')
		{

			++p;
		} else
		{
			if (*p == END_OPTION_STRING ||
			    (validchars != NULL && strchr(validchars, *p) == NULL))

				break;
		}
		*out++ = *p;
	}
	*out = '\0';
	return (p);
}
