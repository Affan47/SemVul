git_diff_patch_to_str(
	char **string,
	git_diff_patch *patch)
{
	int error;
	git_buf output = GIT_BUF_INIT;

	error = git_diff_patch_print(patch, print_to_buffer_cb, &output);


	if (error == GIT_EUSER)
		error = -1;

	*string = git_buf_detach(&output);

	return error;
}
