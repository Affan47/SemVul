window_reload(Win *win, Text *text) {
	win->text = text;
	window_selection_clear(win);
	window_cursor_to(win, 0);
	if (win->ui)
		win->ui->reload(win->ui, text);
}
