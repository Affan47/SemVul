status_run(struct view *view, const char *argv[], char status, enum line_type type)
{
	struct status *file = NULL;
	struct status *unmerged = NULL;
	char *buf;
	struct io io = {};

	if (!run_io(&io, argv, NULL, IO_RD))
		return FALSE;

	add_line_data(view, NULL, type);

	while ((buf = io_get(&io, 0, TRUE))) {
		if (!file) {
			if (!realloc_lines(view, view->line_size + 1))
				goto error_out;

			file = calloc(1, sizeof(*file));
			if (!file)
				goto error_out;

			add_line_data(view, file, type);
		}


		if (status) {
			file->status = status;
			if (status == 'A')
				string_copy(file->old.rev, NULL_ID);

		} else if (!file->status) {
			if (!status_get_diff(file, buf, strlen(buf)))
				goto error_out;

			buf = io_get(&io, 0, TRUE);
			if (!buf)
				break;


			if (file->status == 'U') {
				unmerged = file;

			} else if (unmerged) {
				int collapse = !strcmp(buf, unmerged->new.name);

				unmerged = NULL;
				if (collapse) {
					free(file);
					view->lines--;
					continue;
				}
			}
		}


		if (!*file->old.name &&
		    (file->status == 'R' || file->status == 'C')) {
			string_ncopy(file->old.name, buf, strlen(buf));

			buf = io_get(&io, 0, TRUE);
			if (!buf)
				break;
		}


		string_ncopy(file->new.name, buf, strlen(buf));
		if (!*file->old.name)
			string_copy(file->old.name, file->new.name);
		file = NULL;
	}

	if (io_error(&io)) {
error_out:
		done_io(&io);
		return FALSE;
	}

	if (!view->line[view->lines - 1].data)
		add_line_data(view, NULL, LINE_STAT_NONE);

	done_io(&io);
	return TRUE;
}
