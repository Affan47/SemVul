get_input(int prompt_position)
{
	struct view *view;
	int i, key, cursor_y, cursor_x;

	if (prompt_position)
		input_mode = TRUE;

	while (TRUE) {
		bool loading = FALSE;

		foreach_view (view, i) {
			update_view(view);
			if (view_is_displayed(view) && view->has_scrolled &&
			    use_scroll_redrawwin)
				redrawwin(view->win);
			view->has_scrolled = FALSE;
			if (view->pipe)
				loading = TRUE;
		}


		if (prompt_position) {
			getbegyx(status_win, cursor_y, cursor_x);
			cursor_x = prompt_position;
		} else {
			view = display[current_view];
			getbegyx(view->win, cursor_y, cursor_x);
			cursor_x = view->width - 1;
			cursor_y += view->lineno - view->offset;
		}
		setsyx(cursor_y, cursor_x);


		doupdate();
		nodelay(status_win, loading);
		key = wgetch(status_win);


		if (key == ERR) {

		} else if (key == KEY_RESIZE) {
			int height, width;

			getmaxyx(stdscr, height, width);

			wresize(status_win, 1, width);
			mvwin(status_win, height - 1, 0);
			wnoutrefresh(status_win);
			resize_display();
			redraw_display(TRUE);

		} else {
			input_mode = FALSE;
			if (key == erasechar())
				key = KEY_BACKSPACE;
			return key;
		}
	}
}
