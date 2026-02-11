test_merge_workdir_simple__initialize(void)
{
	git_config *cfg;

	repo = cl_git_sandbox_init(TEST_REPO_PATH);
	git_repository_index(&repo_index, repo);


	cl_git_pass(git_repository_config(&cfg, repo));
	cl_git_pass(git_config_set_string(cfg, "merge.conflictstyle", "merge"));
	git_config_free(cfg);
}
