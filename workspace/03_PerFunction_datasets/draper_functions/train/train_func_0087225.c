draw_view_line(struct view *view, unsigned int lineno)
{
	struct line *line;
	bool selected = (view->offset + lineno == view->lineno);
	bool draw_ok;

	assert(view_is_displayed(view));

	if (view->offset + lineno >= view->lines)
		return FALSE;

	line = &view->line[view->offset + lineno];

	wmove(view->win, lineno, 0);
	view->col = 0;
	view->curline = line;
	view->curtype = LINE_NONE;
	line->selected = FALSE;

	if (selected) {
		set_view_attr(view, LINE_CURSOR);
		line->selected = TRUE;
		view->ops->select(view, line);
	} else if (line->selected) {
		wclrtoeol(view->win);
	}

	scrollok(view->win, FALSE);
	draw_ok = view->ops->draw(view, line, lineno);
	scrollok(view->win, TRUE);

	return draw_ok;
}
