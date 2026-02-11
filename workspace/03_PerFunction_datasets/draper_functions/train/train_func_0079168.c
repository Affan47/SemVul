remove_parameters (const char *exec)
{
	GString *str;
	char    *retval, *p;

	str = g_string_new (exec);

	while ((p = strstr (str->str, "%"))) {
		switch (p [1]) {
		case '%':
			g_string_erase (str, p - str->str, 1);
			break;
		case 'U':
		case 'F':
		case 'N':
		case 'D':
		case 'f':
		case 'u':
		case 'd':
		case 'n':
		case 'm':
		case 'i':
		case 'c':
		case 'k':
		case 'v':
			g_string_erase (str, p - str->str, 2);
			break;
		default:
			break;
		}
	}

	retval = str->str;
	g_string_free (str, FALSE);

	return retval;
}
