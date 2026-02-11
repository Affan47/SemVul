mystrdup(char *s)
{


	char	*t;

	t = (char *) MyMalloc(strlen(s) + 1);
	if (t)
		return ((char *)strcpy(t, s));
	return NULL;
}
