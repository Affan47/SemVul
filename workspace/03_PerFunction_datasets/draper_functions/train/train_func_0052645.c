git_futils_cleanupdir_r(const char *path)
{
	int error;
	git_buf fullpath = GIT_BUF_INIT;
	futils__rmdir_data data;

	if ((error = git_buf_put(&fullpath, path, strlen(path))) < 0)
		goto clean_up;

	data.base    = "";
	data.baselen = 0;
	data.flags   = GIT_RMDIR_REMOVE_FILES;
	data.error   = 0;

	if (!git_path_exists(path)) {
		giterr_set(GITERR_OS, "Path does not exist: %s" , path);
		error = GIT_ERROR;
		goto clean_up;
	}

	if (!git_path_isdir(path)) {
		giterr_set(GITERR_OS, "Path is not a directory: %s" , path);
		error = GIT_ERROR;
		goto clean_up;
	}

	error = git_path_direach(&fullpath, futils__rmdir_recurs_foreach, &data);
	if (error == GIT_EUSER)
		error = data.error;

clean_up:
	git_buf_free(&fullpath);
	return error;
}
