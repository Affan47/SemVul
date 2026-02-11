test_diff_diffiter__iterate_files_and_hunks(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_diff_options opts = {0};
	git_diff_list *diff = NULL;
	size_t d, num_d;
	int file_count = 0, hunk_count = 0;

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_workdir_to_index(&diff, repo, NULL, &opts));

	num_d = git_diff_num_deltas(diff);

	for (d = 0; d < num_d; ++d) {
		git_diff_patch *patch;
		const git_diff_delta *delta;
		size_t h, num_h;

		cl_git_pass(git_diff_get_patch(&patch, &delta, diff, d));

		cl_assert(delta);
		cl_assert(patch);

		file_count++;

		num_h = git_diff_patch_num_hunks(patch);

		for (h = 0; h < num_h; h++) {
			const git_diff_range *range;
			const char *header;
			size_t header_len, num_l;

			cl_git_pass(git_diff_patch_get_hunk(
				&range, &header, &header_len, &num_l, patch, h));

			cl_assert(range);
			cl_assert(header);

			hunk_count++;
		}

		git_diff_patch_free(patch);
	}

	cl_assert_equal_i(13, file_count);
	cl_assert_equal_i(8, hunk_count);

	git_diff_list_free(diff);
}
