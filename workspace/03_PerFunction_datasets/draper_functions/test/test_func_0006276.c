status_update_files(struct view *view, struct line *line)
{
	struct io io = {};
	bool result = TRUE;
	struct line *pos = view->line + view->lines;
	int files = 0;
	int file, done;

	if (!status_update_prepare(&io, line->type))
		return FALSE;

	for (pos = line; pos < view->line + view->lines && pos->data; pos++)
		files++;

	for (file = 0, done = 0; result && file < files; line++, file++) {
		int almost_done = file * 100 / files;

		if (almost_done > done) {
			done = almost_done;
			string_format(view->ref, "updating file %u of %u (%d%% done)",
				      file, files, done);
			update_view_title(view);
		}
		result = status_update_write(&io, line->data, line->type);
	}

	done_io(&io);
	return result;
}
