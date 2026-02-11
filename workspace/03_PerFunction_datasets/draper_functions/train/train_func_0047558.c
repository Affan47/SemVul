test_repo_setters__setting_a_workdir_creates_a_gitlink(void)
{
	git_config *cfg;
	const char *val;
	git_buf content = GIT_BUF_INIT;

	cl_git_pass(git_repository_set_workdir(repo, "./new_workdir", true));

	cl_assert(git_path_isfile("./new_workdir/.git"));

	cl_git_pass(git_futils_readbuffer(&content, "./new_workdir/.git"));
	cl_assert(git__prefixcmp(git_buf_cstr(&content), "gitdir: ") == 0);
	cl_assert(git__suffixcmp(git_buf_cstr(&content), "testrepo.git/") == 0);
	git_buf_free(&content);

	cl_git_pass(git_repository_config(&cfg, repo));
	cl_git_pass(git_config_get_string(&val, cfg, "core.worktree"));
	cl_assert(git__suffixcmp(val, "new_workdir/") == 0);
	git_config_free(cfg);
}
