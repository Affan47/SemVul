redraw_view_dirty(struct view *view)
{
	bool dirty = FALSE;
	int lineno;

	for (lineno = 0; lineno < view->height; lineno++) {
		struct line *line = &view->line[view->offset + lineno];

		if (!line->dirty)
			continue;
		line->dirty = 0;
		dirty = TRUE;
		if (!draw_view_line(view, lineno))
			break;
	}

	if (!dirty)
		return;
	redrawwin(view->win);
	if (input_mode)
		wnoutrefresh(view->win);
	else
		wrefresh(view->win);
}
