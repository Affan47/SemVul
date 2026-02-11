test_diff_rename__file_exchange_three(void)
{
	git_buf c1 = GIT_BUF_INIT, c2 = GIT_BUF_INIT, c3 = GIT_BUF_INIT;
	git_index *index;
	git_tree *tree;
	git_diff_list *diff;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options opts = GIT_DIFF_FIND_OPTIONS_INIT;
	diff_expects exp;

	cl_git_pass(git_futils_readbuffer(&c1, "renames/untimely.txt"));
	cl_git_pass(git_futils_readbuffer(&c2, "renames/songof7cities.txt"));
	cl_git_pass(git_futils_readbuffer(&c3, "renames/ikeepsix.txt"));

	cl_git_pass(git_futils_writebuffer(&c1, "renames/ikeepsix.txt", 0, 0));
	cl_git_pass(git_futils_writebuffer(&c2, "renames/untimely.txt", 0, 0));
	cl_git_pass(git_futils_writebuffer(&c3, "renames/songof7cities.txt", 0, 0));

	cl_git_pass(
		git_revparse_single((git_object **)&tree, g_repo, "HEAD^{tree}"));

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_read_tree(index, tree));
	cl_git_pass(git_index_add_bypath(index, "songof7cities.txt"));
	cl_git_pass(git_index_add_bypath(index, "untimely.txt"));
	cl_git_pass(git_index_add_bypath(index, "ikeepsix.txt"));

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, tree, index, &diffopts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(3, exp.files);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);

	opts.flags = GIT_DIFF_FIND_ALL;
	cl_git_pass(git_diff_find_similar(diff, &opts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(3, exp.files);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_RENAMED]);

	git_diff_list_free(diff);
	git_tree_free(tree);
	git_index_free(index);

	git_buf_free(&c1);
	git_buf_free(&c2);
	git_buf_free(&c3);
}
