stripoff_last_component(char *path)
{
	char *p = strrchr(path, '/');

	if (!p)
		return NULL;
	*p = '\0';
	return ++p;
}
