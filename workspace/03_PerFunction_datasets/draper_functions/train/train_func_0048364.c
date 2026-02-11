draw_chars(struct view *view, enum line_type type, const char *string,
	   int max_len, bool use_tilde)
{
	int len = 0;
	int col = 0;
	int trimmed = FALSE;
	size_t skip = view->yoffset > view->col ? view->yoffset - view->col : 0;

	if (max_len <= 0)
		return 0;

	if (opt_utf8) {
		len = utf8_length(&string, skip, &col, max_len, &trimmed, use_tilde);
	} else {
		col = len = strlen(string);
		if (len > max_len) {
			if (use_tilde) {
				max_len -= 1;
			}
			col = len = max_len;
			trimmed = TRUE;
		}
	}

	set_view_attr(view, type);
	if (len > 0)
		waddnstr(view->win, string, len);
	if (trimmed && use_tilde) {
		set_view_attr(view, LINE_DELIMITER);
		waddch(view->win, '~');
		col++;
	}

	if (view->col + col >= view->width + view->yoffset)
		view->can_hscroll = TRUE;

	return col;
}
