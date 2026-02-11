test_diff_workdir__larger_hunks(void)
{
	const char *a_commit = "d70d245ed97ed2aa596dd1af6536e4bfdb047b69";
	const char *b_commit = "7a9e0b02e63179929fed24f0a3e0f19168114d10";
	git_tree *a, *b;
	git_diff_options opts = {0};
	size_t i, d, num_d, h, num_h, l, num_l, header_len, line_len;

	g_repo = cl_git_sandbox_init("diff");

	cl_assert((a = resolve_commit_oid_to_tree(g_repo, a_commit)) != NULL);
	cl_assert((b = resolve_commit_oid_to_tree(g_repo, b_commit)) != NULL);

	opts.context_lines = 1;
	opts.interhunk_lines = 0;

	for (i = 0; i <= 2; ++i) {
		git_diff_list *diff = NULL;
		git_diff_patch *patch;
		const git_diff_range *range;
		const char *header, *line;
		char origin;


		switch (i) {
		case 0:
			cl_git_pass(git_diff_workdir_to_index(&diff, g_repo, NULL, &opts));
			break;
		case 1:
			cl_git_pass(git_diff_workdir_to_tree(&diff, g_repo, a, &opts));
			break;
		case 2:
			cl_git_pass(git_diff_workdir_to_tree(&diff, g_repo, b, &opts));
			break;
		}

		num_d = git_diff_num_deltas(diff);
		cl_assert_equal_i(2, (int)num_d);

		for (d = 0; d < num_d; ++d) {
			cl_git_pass(git_diff_get_patch(&patch, NULL, diff, d));
			cl_assert(patch);

			num_h = git_diff_patch_num_hunks(patch);
			for (h = 0; h < num_h; h++) {
				cl_git_pass(git_diff_patch_get_hunk(
					&range, &header, &header_len, &num_l, patch, h));

				for (l = 0; l < num_l; ++l) {
					cl_git_pass(git_diff_patch_get_line_in_hunk(
						&origin, &line, &line_len, NULL, NULL, patch, h, l));
					cl_assert(line);
				}


				cl_git_fail(git_diff_patch_get_line_in_hunk(
					&origin, &line, &line_len, NULL, NULL, patch, h, num_l));
			}


			cl_git_fail(git_diff_patch_get_hunk(
				&range, &header, &header_len, &num_l, patch, num_h));

			git_diff_patch_free(patch);
		}

		git_diff_list_free(diff);
	}

	git_tree_free(a);
	git_tree_free(b);
}
