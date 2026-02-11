repo_init_create_origin(git_repository *repo, const char *url)
{
	int error;
	git_remote *remote;

	if (!(error = git_remote_add(&remote, repo, GIT_REMOTE_ORIGIN, url))) {
		error = git_remote_save(remote);
		git_remote_free(remote);
	}

	return error;
}
