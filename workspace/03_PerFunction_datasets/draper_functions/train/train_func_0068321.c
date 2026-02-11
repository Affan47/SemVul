test_status_worktree__purged_worktree(void)
{
	status_entry_counts counts;
	git_repository *repo = cl_git_sandbox_init("status");
	git_buf workdir = GIT_BUF_INIT;


	cl_git_pass(git_buf_sets(&workdir, git_repository_workdir(repo)));
	cl_git_pass(git_path_direach(&workdir, remove_file_cb, NULL));
	git_buf_free(&workdir);


	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = entry_count2;
	counts.expected_paths = entry_paths2;
	counts.expected_statuses = entry_statuses2;

	cl_git_pass(
		git_status_foreach(repo, cb_status__normal, &counts)
	);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}
