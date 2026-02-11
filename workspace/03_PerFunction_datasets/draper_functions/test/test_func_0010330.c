test_status_worktree__line_endings_dont_count_as_changes_with_autocrlf(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_config *config;
	unsigned int status;

	cl_git_pass(git_repository_config(&config, repo));
	cl_git_pass(git_config_set_bool(config, "core.autocrlf", true));
	git_config_free(config);

	cl_git_rewritefile("status/current_file", "current_file\r\n");

	cl_git_pass(git_status_file(&status, repo, "current_file"));

	cl_assert_equal_i(GIT_STATUS_CURRENT, status);
}
