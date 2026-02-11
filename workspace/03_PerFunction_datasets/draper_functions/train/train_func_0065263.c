attr_setup(git_repository *repo)
{
	int error = 0;
	const char *workdir = git_repository_workdir(repo);
	git_index *idx = NULL;
	git_buf sys = GIT_BUF_INIT;

	if ((error = git_attr_cache__init(repo)) < 0)
		return error;


	if (!(error = git_sysdir_find_system_file(&sys, GIT_ATTR_FILE_SYSTEM))) {
		error = preload_attr_file(
			repo, GIT_ATTR_FILE__FROM_FILE, NULL, sys.ptr);
		git_buf_free(&sys);
	}
	if (error < 0) {
		if (error == GIT_ENOTFOUND) {
			giterr_clear();
			error = 0;
		} else
			return error;
	}

	if ((error = preload_attr_file(
			repo, GIT_ATTR_FILE__FROM_FILE,
			NULL, git_repository_attr_cache(repo)->cfg_attr_file)) < 0)
		return error;

	if ((error = preload_attr_file(
			repo, GIT_ATTR_FILE__FROM_FILE,
			git_repository_path(repo), GIT_ATTR_FILE_INREPO)) < 0)
		return error;

	if (workdir != NULL &&
		(error = preload_attr_file(
			repo, GIT_ATTR_FILE__FROM_FILE, workdir, GIT_ATTR_FILE)) < 0)
		return error;

	if ((error = git_repository_index__weakptr(&idx, repo)) < 0 ||
		(error = preload_attr_file(
			repo, GIT_ATTR_FILE__FROM_INDEX, NULL, GIT_ATTR_FILE)) < 0)
		return error;

	return error;
}
