ensure_normalized(const char *input_path, const char *expected_path, normalize_path normalizer, int assert_flags)
{
	int error = GIT_SUCCESS;
	char buffer_out[GIT_PATH_MAX];
	char current_workdir[GIT_PATH_MAX];

	error = gitfo_getcwd(current_workdir, sizeof(current_workdir));
	if (error < GIT_SUCCESS)
		return error;

	error = normalizer(buffer_out, sizeof(buffer_out), input_path);
	if (error < GIT_SUCCESS)
		return error;

	if (expected_path == NULL)
		return error;

	if ((assert_flags & PATH_AS_SUFFIX) != 0)
		if (git__suffixcmp(buffer_out, expected_path))
			return GIT_ERROR;

	if ((assert_flags & CWD_AS_PREFIX) != 0)
		if (git__prefixcmp(buffer_out, current_workdir))
			return GIT_ERROR;

	if ((assert_flags & ROOTED_PATH) != 0) {
		error = strcmp(expected_path, buffer_out);
	}

	return error;
}
