open_gitmodules(
	git_repository *repo,
	bool okay_to_create,
	const git_oid *gitmodules_oid)
{
	const char *workdir = git_repository_workdir(repo);
	git_buf path = GIT_BUF_INIT;
	git_config_backend *mods = NULL;

	if (workdir != NULL) {
		if (git_buf_joinpath(&path, workdir, GIT_MODULES_FILE) != 0)
			return NULL;

		if (okay_to_create || git_path_isfile(path.ptr)) {

			if (git_config_file__ondisk(&mods, path.ptr) < 0)
				mods = NULL;

			else if (git_config_file_open(mods, GIT_CONFIG_LEVEL_LOCAL) < 0) {
				git_config_file_free(mods);
				mods = NULL;
			}
		}
	}

	if (!mods && gitmodules_oid && !git_oid_iszero(gitmodules_oid)) {


	}

	git_buf_free(&path);

	return mods;
}
