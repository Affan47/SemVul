ui_window_options(UiWin *w, enum UiOption options) {
	UiCursesWin *win = (UiCursesWin*)w;
	win->options = options;
	switch (options) {
	case UI_OPTION_LINE_NUMBERS_NONE:
		if (win->winside) {
			delwin(win->winside);
			win->winside = NULL;
			win->sidebar_width = 0;
		}
		break;
	case UI_OPTION_LINE_NUMBERS_ABSOLUTE:
	case UI_OPTION_LINE_NUMBERS_RELATIVE:
		if (!win->winside)
			win->winside = newwin(1, 1, 1, 1);
		break;
	}
	ui_window_draw(w);
}
