trim_directory(char *path)
{
	char	   *p;

	path = skip_drive(path);

	if (path[0] == '\0')
		return;


	for (p = path + strlen(path) - 1; IS_DIR_SEP(*p) && p > path; p--)
		;

	for (; !IS_DIR_SEP(*p) && p > path; p--)
		;

	for (; p > path && IS_DIR_SEP(*(p - 1)); p--)
		;

	if (p == path && IS_DIR_SEP(*p))
		p++;
	*p = '\0';
}
