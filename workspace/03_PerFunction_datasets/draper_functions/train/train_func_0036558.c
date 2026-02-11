pg_check_dir(const char *dir)
{
	int			result = 1;
	DIR		   *chkdir;
	struct dirent *file;

	errno = 0;

	chkdir = opendir(dir);

	if (chkdir == NULL)
		return (errno == ENOENT) ? 0 : -1;

	while ((file = readdir(chkdir)) != NULL)
	{
		if (strcmp(".", file->d_name) == 0 ||
			strcmp("..", file->d_name) == 0)
		{

			continue;
		}
		else
		{
			result = 2;
			break;
		}
	}

#ifdef WIN32


	if (GetLastError() == ERROR_NO_MORE_FILES)
		errno = 0;
#endif

	closedir(chkdir);

	if (errno != 0)
		result = -1;

	return result;
}
