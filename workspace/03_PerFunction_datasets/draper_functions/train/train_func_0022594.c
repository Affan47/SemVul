window_scroll_to(Win *win, size_t pos) {
	while (pos < win->start && window_viewport_up(win, 1));
	while (pos > win->end && window_viewport_down(win, 1));
	window_cursor_to(win, pos);
}
