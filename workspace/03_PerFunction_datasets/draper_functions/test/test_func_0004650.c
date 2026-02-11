test_status_ignore__0(void)
{
	struct {
		const char *path;
		int expected;
	} test_cases[] = {

		{ "file", 0 },
		{ "ign", 1 },
		{ "sub", 0 },
		{ "sub/file", 0 },
		{ "sub/ign", 1 },
		{ "sub/ign/file", 1 },
		{ "sub/ign/sub", 1 },
		{ "sub/ign/sub/file", 1 },
		{ "sub/sub", 0 },
		{ "sub/sub/file", 0 },
		{ "sub/sub/ign", 1 },
		{ "sub/sub/sub", 0 },

		{ "dir", 1 },
		{ "dir/", 1 },
		{ "sub/dir", 1 },
		{ "sub/dir/", 1 },
		{ "sub/dir/file", 1 },
		{ "sub/sub/dir", 0 },
		{ NULL, 0 }
	}, *one_test;

	g_repo = cl_git_sandbox_init("attr");

	for (one_test = test_cases; one_test->path != NULL; one_test++)
		assert_ignored(one_test->expected, one_test->path);


	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, ".git/info/exclude"));
	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, ".gitignore"));
}
