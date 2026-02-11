rename_remote_config_section(
	git_repository *repo,
	const char *old_name,
	const char *new_name)
{
	git_buf old_section_name = GIT_BUF_INIT,
		new_section_name = GIT_BUF_INIT;
	int error = -1;

	if (git_buf_printf(&old_section_name, "remote.%s", old_name) < 0)
		goto cleanup;

	if (new_name &&
		(git_buf_printf(&new_section_name, "remote.%s", new_name) < 0))
			goto cleanup;

	error = git_config_rename_section(
		repo,
		git_buf_cstr(&old_section_name),
		new_name ? git_buf_cstr(&new_section_name) : NULL);

cleanup:
	git_buf_free(&old_section_name);
	git_buf_free(&new_section_name);

	return error;
}
