to_abs_path_directory_base(const char *rel_path, char *abs_path, size_t size)
{
	int ret;

	ret = chdir_backup(rel_path);
	if (ret < 0)
	{
		return NULL;
	}

	if (getcwd(abs_path, size) == NULL)
	{
		abs_path = NULL;
	}

	chdir_backup(NULL);

	return abs_path;
}
