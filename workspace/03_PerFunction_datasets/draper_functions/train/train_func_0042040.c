test_repo_iterator__fs2(void)
{
	git_iterator *i;
	static const char *expect_base[] = {
		"heads/br2",
		"heads/dir",
		"heads/long-file-name",
		"heads/master",
		"heads/packed-test",
		"heads/subtrees",
		"heads/test",
		"tags/e90810b",
		"tags/foo/bar",
		"tags/foo/foo/bar",
		"tags/point_to_blob",
		"tags/test",
		NULL,
	};

	g_repo = cl_git_sandbox_init("testrepo");

	cl_git_pass(git_iterator_for_filesystem(
		&i, "testrepo/.git/refs", 0, NULL, NULL));
	expect_iterator_items(i, 12, expect_base, 12, expect_base);
	git_iterator_free(i);
}
