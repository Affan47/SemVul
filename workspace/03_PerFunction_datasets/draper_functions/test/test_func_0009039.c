git_diff_file_stats__full_to_buf(
	git_buf *out,
	const git_diff_delta *delta,
	const diff_file_stats *filestat,
	const git_diff_stats *stats,
	size_t width)
{
	const char *old_path = NULL, *new_path = NULL;
	size_t padding, old_size, new_size;

	old_path = delta->old_file.path;
	new_path = delta->new_file.path;
	old_size = delta->old_file.size;
	new_size = delta->new_file.size;

	if (git_buf_printf(out, " %s", old_path) < 0)
		goto on_error;

	if (strcmp(old_path, new_path) != 0) {
		padding = stats->max_name - strlen(old_path) - strlen(new_path);

		if (git_buf_printf(out, DIFF_RENAME_FILE_SEPARATOR "%s", new_path) < 0)
			goto on_error;
	} else {
		padding = stats->max_name - strlen(old_path);

		if (stats->renames > 0)
			padding += strlen(DIFF_RENAME_FILE_SEPARATOR);
	}

	if (git_buf_putcn(out, ' ', padding) < 0 ||
		git_buf_puts(out, " | ") < 0)
		goto on_error;

	if (delta->flags & GIT_DIFF_FLAG_BINARY) {
		if (git_buf_printf(out,
				"Bin %" PRIuZ " -> %" PRIuZ " bytes", old_size, new_size) < 0)
			goto on_error;
	}
	else {
		if (git_buf_printf(out,
				"%*" PRIuZ, stats->max_digits,
				filestat->insertions + filestat->deletions) < 0)
			goto on_error;

		if (filestat->insertions || filestat->deletions) {
			if (git_buf_putc(out, ' ') < 0)
				goto on_error;

			if (!width) {
				if (git_buf_putcn(out, '+', filestat->insertions) < 0 ||
					git_buf_putcn(out, '-', filestat->deletions) < 0)
					goto on_error;
			} else {
				size_t total = filestat->insertions + filestat->deletions;
				size_t full = (total * width + stats->max_filestat / 2) /
					stats->max_filestat;
				size_t plus = full * filestat->insertions / total;
				size_t minus = full - plus;

				if (git_buf_putcn(out, '+', max(plus,  1)) < 0 ||
					git_buf_putcn(out, '-', max(minus, 1)) < 0)
					goto on_error;
			}
		}
	}

	git_buf_putc(out, '\n');

on_error:
	return (git_buf_oom(out) ? -1 : 0);
}
