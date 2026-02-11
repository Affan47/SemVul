git_futils_rmdir_r(
	const char *path, const char *base, uint32_t flags)
{
	int error;
	git_buf fullpath = GIT_BUF_INIT;
	futils__rmdir_data data;


	if (git_path_join_unrooted(&fullpath, path, base, NULL) < 0)
		return -1;

	memset(&data, 0, sizeof(data));
	data.base    = base ? base : "";
	data.baselen = base ? strlen(base) : 0;
	data.flags   = flags;

	error = futils__rmdir_recurs_foreach(&data, &fullpath);


	if (!error && (flags & GIT_RMDIR_EMPTY_PARENTS) != 0)
		error = git_path_walk_up(
			&fullpath, base, futils__rmdir_empty_parent, &data);

	if (error == GIT_ITEROVER) {
		giterr_clear();
		error = 0;
	}

	git_buf_free(&fullpath);

	return error;
}
