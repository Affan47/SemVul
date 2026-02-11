update_view(struct view *view)
{
	char in_buffer[BUFSIZ];
	char out_buffer[BUFSIZ * 2];
	char *line;


	unsigned long lines = view->height;
	int redraw_from = -1;

	if (!view->pipe)
		return TRUE;


	if (view->offset + view->height >= view->lines)
		redraw_from = view->lines - view->offset;


	if (!realloc_lines(view, view->lines + lines))
		goto alloc_error;

	while ((line = fgets(in_buffer, sizeof(in_buffer), view->pipe))) {
		size_t linelen = strlen(line);

		if (linelen)
			line[linelen - 1] = 0;

		if (opt_iconv != ICONV_NONE) {
			ICONV_CONST char *inbuf = line;
			size_t inlen = linelen;

			char *outbuf = out_buffer;
			size_t outlen = sizeof(out_buffer);

			size_t ret;

			ret = iconv(opt_iconv, &inbuf, &inlen, &outbuf, &outlen);
			if (ret != (size_t) -1) {
				line = out_buffer;
				linelen = strlen(out_buffer);
			}
		}

		if (!view->ops->read(view, line))
			goto alloc_error;

		if (lines-- == 1)
			break;
	}

	{
		int digits;

		lines = view->lines;
		for (digits = 0; lines; digits++)
			lines /= 10;


		if (digits != view->digits) {
			view->digits = digits;
			redraw_from = 0;
		}
	}

	if (!view_is_displayed(view))
		goto check_pipe;

	if (view == VIEW(REQ_VIEW_TREE)) {


		redraw_view(view);

	} else if (redraw_from >= 0) {


		if (redraw_from > 0)
			redraw_from--;


		if (redraw_from > 0 && opt_rev_graph)
			redraw_from--;


		redraw_view_from(view, redraw_from);
	}

	if (view == VIEW(REQ_VIEW_BLAME))
		redraw_view_dirty(view);


	update_view_title(view);

check_pipe:
	if (ferror(view->pipe)) {
		report("Failed to read: %s", strerror(errno));
		goto end;

	} else if (feof(view->pipe)) {
		report("");
		goto end;
	}

	return TRUE;

alloc_error:
	report("Allocation failure");

end:
	if (view->ops->read(view, NULL))
		end_update(view);
	return FALSE;
}
