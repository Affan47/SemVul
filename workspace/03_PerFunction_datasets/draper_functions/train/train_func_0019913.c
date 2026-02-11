redraw_view_from(struct view *view, int lineno)
{
	assert(0 <= lineno && lineno < view->height);

	for (; lineno < view->height; lineno++) {
		if (!draw_view_line(view, lineno))
			break;
	}

	redrawwin(view->win);
	if (input_mode)
		wnoutrefresh(view->win);
	else
		wrefresh(view->win);
}
