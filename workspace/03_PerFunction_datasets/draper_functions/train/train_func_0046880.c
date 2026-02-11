check_removal_cb(
	void *cb_data,
	git_diff_delta *delta,
	git_diff_range *range,
	char line_origin,
	const char *formatted_output,
	size_t output_len)
{
	GIT_UNUSED(cb_data);
	GIT_UNUSED(output_len);

	switch (line_origin) {
	case GIT_DIFF_LINE_FILE_HDR:
		cl_assert_equal_s(EXPECTED_HEADER, formatted_output);
		cl_assert(range == NULL);
		goto check_delta;

	case GIT_DIFF_LINE_HUNK_HDR:
		cl_assert_equal_s(EXPECTED_HUNK, formatted_output);


	case GIT_DIFF_LINE_CONTEXT:
	case GIT_DIFF_LINE_DELETION:
		goto check_range;

	default:

		return -1;
	}

check_range:
	cl_assert(range != NULL);
	cl_assert_equal_i(1, range->old_start);
	cl_assert_equal_i(2, range->old_lines);
	cl_assert_equal_i(0, range->new_start);
	cl_assert_equal_i(0, range->new_lines);

check_delta:
	cl_assert_equal_s("subdir.txt", delta->old_file.path);
	cl_assert_equal_s("subdir.txt", delta->new_file.path);
	cl_assert_equal_i(GIT_DELTA_DELETED, delta->status);

	return 0;
}
