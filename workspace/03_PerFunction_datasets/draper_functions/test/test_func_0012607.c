retrieve_upstream_configuration(
	const char **out,
	const git_config *config,
	const char *canonical_branch_name,
	const char *format)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if (git_buf_printf(&buf, format,
		canonical_branch_name + strlen(GIT_REFS_HEADS_DIR)) < 0)
			return -1;

	error = git_config_get_string(out, config, git_buf_cstr(&buf));
	git_buf_free(&buf);
	return error;
}
