window_line_down(Win *win) {
	Cursor *cursor = &win->cursor;
	if (!cursor->line->next || cursor->line->next->lineno != cursor->line->lineno)
		return window_screenline_down(win);
	size_t bol = text_line_begin(win->text, cursor->pos);
	size_t next = text_line_next(win->text, bol);
	size_t pos = text_line_offset(win->text, next, cursor->pos - bol);
	window_cursor_to(win, pos);
	return cursor->pos;
}
