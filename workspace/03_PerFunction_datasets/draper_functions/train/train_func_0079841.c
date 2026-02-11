gitfo_isfile(const char *path)
{
	struct stat st;
	int stat_error;

	if (!path)
		return git__throw(GIT_ENOTFOUND, "No path given to gitfo_isfile");

	stat_error = gitfo_stat(path, &st);

	if (stat_error < GIT_SUCCESS)
		return git__throw(GIT_ENOTFOUND, "%s does not exist", path);

	if (!S_ISREG(st.st_mode))
		return git__throw(GIT_ENOTFOUND, "%s is not a file", path);

	return GIT_SUCCESS;
}
