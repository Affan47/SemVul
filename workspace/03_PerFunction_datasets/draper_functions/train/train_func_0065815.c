window_redraw_center(Win *win) {
	int center = win->height / 2;
	size_t pos = win->cursor.pos;
	for (int i = 0; i < 2; i++) {
		int linenr = 0;
		Line *line = win->cursor.line;
		for (Line *cur = win->topline; cur && cur != line; cur = cur->next)
			linenr++;
		if (linenr < center) {
			window_slide_down(win, center - linenr);
			continue;
		}
		for (Line *cur = win->topline; cur && cur != line && linenr > center; cur = cur->next) {
			win->start += cur->len;
			linenr--;
		}
		break;
	}
	window_draw(win);
	window_cursor_to(win, pos);
}
