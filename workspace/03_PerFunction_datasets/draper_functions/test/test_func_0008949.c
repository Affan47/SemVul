file_newly_cmp(const char *file1, const char *file2)
{
	struct stat st1, st2;

	if (file_stat2(file1, &st1) < 0)
	{
		return -1;
	}

	if (file_stat2(file2, &st2) < 0)
	{
		return 1;
	}

	return st2.st_mtime - st1.st_mtime;
}
