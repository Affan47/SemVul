git_config_open_global(git_config **out)
{
	int error;
	char global_path[GIT_PATH_MAX];

	if ((error = git_config_find_global(global_path)) < GIT_SUCCESS)
		return error;

	return git_config_open_ondisk(out, global_path);
}
