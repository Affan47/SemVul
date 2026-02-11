test_diff_workdir__submodules(void)
{
	const char *a_commit = "873585b94bdeabccea991ea5e3ec1a277895b698";
	git_tree *a;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;

	g_repo = setup_fixture_submod2();

	a = resolve_commit_oid_to_tree(g_repo, a_commit);

	opts.flags =
		GIT_DIFF_INCLUDE_UNTRACKED |
		GIT_DIFF_INCLUDE_IGNORED |
		GIT_DIFF_RECURSE_UNTRACKED_DIRS |
		GIT_DIFF_SHOW_UNTRACKED_CONTENT;

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, a, &opts));


	memset(&exp, 0, sizeof(exp));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_hunk_cb, diff_line_cb, &exp));


	cl_assert_equal_i(12, exp.files);

	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_IGNORED]);
	cl_assert_equal_i(10, exp.file_status[GIT_DELTA_UNTRACKED]);


	cl_assert_equal_i(9, exp.hunks);

	cl_assert_equal_i(33, exp.lines);
	cl_assert_equal_i(2, exp.line_ctxt);
	cl_assert_equal_i(30, exp.line_adds);
	cl_assert_equal_i(1, exp.line_dels);

	git_diff_free(diff);
	git_tree_free(a);
}
