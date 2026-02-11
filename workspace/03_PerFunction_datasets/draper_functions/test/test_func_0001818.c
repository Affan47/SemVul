test_status_ignore__subdirectories(void)
{
	status_entry_single st;
	int ignored;
	git_status_options opts;

	GIT_UNUSED(opts);

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_mkfile(
		"empty_standard_repo/ignore_me", "I'm going to be ignored!");

	cl_git_rewritefile("empty_standard_repo/.gitignore", "ignore_me\n");

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert_equal_i(2, st.count);
	cl_assert(st.status == GIT_STATUS_IGNORED);

	cl_git_pass(git_status_file(&st.status, g_repo, "ignore_me"));
	cl_assert(st.status == GIT_STATUS_IGNORED);

	cl_git_pass(git_status_should_ignore(&ignored, g_repo, "ignore_me"));
	cl_assert(ignored);


	cl_git_pass(
		git_futils_mkdir_r("empty_standard_repo/test/ignore_me", NULL, 0775));
	cl_git_mkfile(
		"empty_standard_repo/test/ignore_me/file", "I'm going to be ignored!");

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.flags = GIT_STATUS_OPT_INCLUDE_IGNORED |
		GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;

	memset(&st, 0, sizeof(st));
	cl_git_pass(git_status_foreach(g_repo, cb_status__single, &st));
	cl_assert_equal_i(2, st.count);

	cl_git_pass(git_status_file(&st.status, g_repo, "test/ignore_me/file"));
	cl_assert(st.status == GIT_STATUS_IGNORED);

	cl_git_pass(
		git_status_should_ignore(&ignored, g_repo, "test/ignore_me/file"));
	cl_assert(ignored);
}
