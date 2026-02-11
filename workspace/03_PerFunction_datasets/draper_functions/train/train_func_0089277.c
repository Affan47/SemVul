git_reference_normalize_name(
	char *buffer_out,
	size_t buffer_size,
	const char *name,
	unsigned int flags)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if ((error = git_reference__normalize_name(&buf, name, flags)) < 0)
		goto cleanup;

	if (git_buf_len(&buf) > buffer_size - 1) {
		giterr_set(
		GITERR_REFERENCE,
		"The provided buffer is too short to hold the normalization of '%s'", name);
		error = GIT_EBUFS;
		goto cleanup;
	}

	git_buf_copy_cstr(buffer_out, buffer_size, &buf);

	error = 0;

cleanup:
	git_buf_free(&buf);
	return error;
}
