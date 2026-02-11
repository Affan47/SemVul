test_status_worktree__swap_subdir_and_file(void)
{
	status_entry_counts counts;
	git_repository *repo = cl_git_sandbox_init("status");
	git_index *index;
	git_status_options opts;
	bool ignore_case;

	cl_git_pass(git_repository_index(&index, repo));
	ignore_case = index->ignore_case;
	git_index_free(index);


	cl_git_pass(p_rename("status/current_file", "status/swap"));
	cl_git_pass(p_rename("status/subdir", "status/current_file"));
	cl_git_pass(p_rename("status/swap", "status/subdir"));

	cl_git_mkfile("status/.HEADER", "dummy");
	cl_git_mkfile("status/42-is-not-prime.sigh", "dummy");
	cl_git_mkfile("status/README.md", "dummy");


	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = entry_count3;
	counts.expected_paths = ignore_case ? entry_paths3_icase : entry_paths3;
	counts.expected_statuses = ignore_case ? entry_statuses3_icase : entry_statuses3;

	memset(&opts, 0, sizeof(opts));
	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_INCLUDE_IGNORED;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts)
	);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}
