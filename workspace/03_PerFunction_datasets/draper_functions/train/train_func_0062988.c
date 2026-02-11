test_clone_nonetwork__do_not_clean_existing_directory(void)
{
	git_buf path_buf = GIT_BUF_INIT;

	git_buf_put(&path_buf, "./foo", 5);


	p_mkdir("./foo", GIT_DIR_MODE);
	cl_git_fail(git_clone(&g_repo, "not_a_repo", "./foo", &g_options));
	cl_assert(git_path_exists("./foo"));


	cl_git_pass(git_path_direach(&path_buf,
		dont_call_me,
		NULL));


	g_options.bare = true;
	cl_git_fail(git_clone(&g_repo, "not_a_repo", "./foo", &g_options));
	cl_assert(git_path_exists("./foo"));


	cl_git_pass(git_path_direach(&path_buf,
		dont_call_me,
		NULL));

	git_buf_free(&path_buf);
}
