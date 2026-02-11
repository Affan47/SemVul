git_diff_print_patch(
	git_diff_list *diff,
	git_diff_data_cb print_cb,
	void *payload)
{
	int error;
	git_buf buf = GIT_BUF_INIT;
	diff_print_info pi;

	if (!(error = diff_print_info_init(&pi, &buf, diff, print_cb, payload)))
		error = git_diff_foreach(
			diff, diff_print_patch_file, diff_print_patch_hunk,
			diff_print_patch_line, &pi);

	git_buf_free(&buf);

	return error;
}
