archive_list_file(struct cmd_context *cmd, const char *file)
{
	struct archive_file af;

	af.path = file;

	if (!path_exists(af.path)) {
		log_error("Archive file %s not found.", af.path);
		return 0;
	}

	_display_archive(cmd, &af);

	return 1;
}
