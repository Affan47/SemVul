get_first_line(char *txt)
{
	char *t = xstrdup(txt);
	char *p = strchr(t, '\n');
	if (p)
		*p = '\0';
	return t;
}
