optstring(s, p_str, printopt, validchars)
	char *s;
	char **p_str;
	char *printopt;
	char *validchars;
{
	register char *p;

	if (*s == '\0')
	{
		nostring(printopt);
		quit(QUIT_ERROR);
	}
	*p_str = s;
	for (p = s;  *p != '\0';  p++)
	{
		if (*p == END_OPTION_STRING ||
		    (validchars != NULL && strchr(validchars, *p) == NULL))
		{
			switch (*p)
			{
			case END_OPTION_STRING:
			case ' ':  case '\t':  case '-':

				*p++ = '\0';
				break;
			default:

				*p_str = (char *) ecalloc(p-s+1, sizeof(char));
				strncpy(*p_str, s, p-s);
				(*p_str)[p-s] = '\0';
				break;
			}
			break;
		}
	}
	return (p);
}
