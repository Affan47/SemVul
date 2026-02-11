test_repo_init__can_reinit_an_initialized_repository(void)
{
	git_repository *reinit;

	cl_set_cleanup(&cleanup_repository, "extended");

	cl_git_pass(git_futils_mkdir("extended", NULL, 0775, 0));
	cl_git_pass(git_repository_init(&_repo, "extended", false));

	cl_git_pass(git_repository_init(&reinit, "extended", false));

	cl_assert_equal_s(git_repository_path(_repo), git_repository_path(reinit));

	git_repository_free(reinit);
}
