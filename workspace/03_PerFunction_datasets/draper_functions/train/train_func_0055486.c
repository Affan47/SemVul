trim_end(const char *str, char c)
{
	int len;
	char *s, *t;

	if (str == NULL)
		return NULL;
	t = (char *)str;
	len = strlen(t);
	while(len > 0 && t[len - 1] == c)
		len--;

	if (len == 0)
		return NULL;

	c = t[len];
	t[len] = '\0';
	s = xstrdup(t);
	t[len] = c;
	return s;
}
