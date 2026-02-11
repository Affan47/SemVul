git_futils_rmdir_r(const char *path, git_directory_removal_type removal_type)
{
	int error;
	git_buf p = GIT_BUF_INIT;

	error = git_buf_sets(&p, path);
	if (!error)
		error = _rmdir_recurs_foreach(&removal_type, &p);
	git_buf_free(&p);
	return error;
}
