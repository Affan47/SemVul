test_status_ignore__contained_dir_with_matching_name(void)
{
	static const char *test_files[] = {
		"empty_standard_repo/subdir_match/aaa/subdir_match/file",
		"empty_standard_repo/subdir_match/zzz_ignoreme",
		NULL
	};
	static const char *expected_paths[] = {
		"subdir_match/.gitignore",
		"subdir_match/aaa/subdir_match/file",
		"subdir_match/zzz_ignoreme",
	};
	static const unsigned int expected_statuses[] = {
		GIT_STATUS_WT_NEW,  GIT_STATUS_WT_NEW,  GIT_STATUS_IGNORED
	};
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	status_entry_counts counts;

	make_test_data("empty_standard_repo", test_files);
	cl_git_mkfile(
		"empty_standard_repo/subdir_match/.gitignore", "*_ignoreme\n");

	refute_is_ignored("subdir_match/aaa/subdir_match/file");
	assert_is_ignored("subdir_match/zzz_ignoreme");

	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = 3;
	counts.expected_paths = expected_paths;
	counts.expected_statuses = expected_statuses;

	opts.flags = GIT_STATUS_OPT_DEFAULTS | GIT_STATUS_OPT_RECURSE_IGNORED_DIRS;

	cl_git_pass(git_status_foreach_ext(
		g_repo, &opts, cb_status__normal, &counts));

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}
