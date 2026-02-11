load_workdir(git_repository *repo, git_buf *parent_path)
{
	int         error;
	git_config *config;
	const char *worktree;
	git_buf     worktree_buf = GIT_BUF_INIT;

	if (repo->is_bare)
		return 0;

	if (git_repository_config__weakptr(&config, repo) < 0)
		return -1;

	error = git_config_get_string(&worktree, config, "core.worktree");
	if (!error && worktree != NULL) {
		error = git_path_prettify_dir(
			&worktree_buf, worktree, repo->path_repository);
		if (error < 0)
			return error;
		repo->workdir = git_buf_detach(&worktree_buf);
	}
	else if (error != GIT_ENOTFOUND)
		return error;
	else {
		giterr_clear();

		if (parent_path && git_path_isdir(parent_path->ptr))
			repo->workdir = git_buf_detach(parent_path);
		else {
			git_path_dirname_r(&worktree_buf, repo->path_repository);
			git_path_to_dir(&worktree_buf);
			repo->workdir = git_buf_detach(&worktree_buf);
		}
	}

	GITERR_CHECK_ALLOC(repo->workdir);

	return 0;
}
