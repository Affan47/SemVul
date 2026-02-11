update_view(struct view *view)
{
	char out_buffer[BUFSIZ * 2];
	char *line;


	bool redraw = view->lines == 0;
	bool can_read = TRUE;

	if (!view->pipe)
		return TRUE;

	if (!io_can_read(view->pipe)) {
		if (view->lines == 0) {
			time_t secs = time(NULL) - view->start_time;

			if (secs > 1 && secs > view->update_secs) {
				if (view->update_secs == 0)
					redraw_view(view);
				update_view_title(view);
				view->update_secs = secs;
			}
		}
		return TRUE;
	}

	for (; (line = io_get(view->pipe, '\n', can_read)); can_read = FALSE) {
		if (opt_iconv != ICONV_NONE) {
			ICONV_CONST char *inbuf = line;
			size_t inlen = strlen(line) + 1;

			char *outbuf = out_buffer;
			size_t outlen = sizeof(out_buffer);

			size_t ret;

			ret = iconv(opt_iconv, &inbuf, &inlen, &outbuf, &outlen);
			if (ret != (size_t) -1)
				line = out_buffer;
		}

		if (!view->ops->read(view, line)) {
			report("Allocation failure");
			end_update(view, TRUE);
			return FALSE;
		}
	}

	{
		unsigned long lines = view->lines;
		int digits;

		for (digits = 0; lines; digits++)
			lines /= 10;


		if (digits != view->digits) {
			view->digits = digits;
			if (opt_line_number || view == VIEW(REQ_VIEW_BLAME))
				redraw = TRUE;
		}
	}

	if (io_error(view->pipe)) {
		report("Failed to read: %s", io_strerror(view->pipe));
		end_update(view, TRUE);

	} else if (io_eof(view->pipe)) {
		report("");
		end_update(view, FALSE);
	}

	if (restore_view_position(view))
		redraw = TRUE;

	if (!view_is_displayed(view))
		return TRUE;

	if (redraw)
		redraw_view_from(view, 0);
	else
		redraw_view_dirty(view);


	update_view_title(view);
	return TRUE;
}
