open_view(struct view *prev, enum request request, enum open_flags flags)
{
	bool split = !!(flags & OPEN_SPLIT);
	bool reload = !!(flags & (OPEN_RELOAD | OPEN_REFRESH | OPEN_PREPARED));
	bool nomaximize = !!(flags & OPEN_REFRESH);
	struct view *view = VIEW(request);
	int nviews = displayed_views();
	struct view *base_view = display[0];

	if (view == prev && nviews == 1 && !reload) {
		report("Already in %s view", view->name);
		return;
	}

	if (view->git_dir && !opt_git_dir[0]) {
		report("The %s view is disabled in pager view", view->name);
		return;
	}

	if (split) {
		display[1] = view;
		current_view = 1;
	} else if (!nomaximize) {

		memset(display, 0, sizeof(display));
		current_view = 0;
		display[current_view] = view;
	}


	if (prev && view != prev) {
		view->parent = prev;
	}


	if (nviews != displayed_views() ||
	    (nviews == 1 && base_view != display[0]))
		resize_display();

	if (view->ops->open) {
		if (view->pipe)
			end_update(view, TRUE);
		if (!view->ops->open(view)) {
			report("Failed to load %s view", view->name);
			return;
		}
		restore_view_position(view);

	} else if ((reload || strcmp(view->vid, view->id)) &&
		   !begin_update(view, flags & (OPEN_REFRESH | OPEN_PREPARED))) {
		report("Failed to load %s view", view->name);
		return;
	}

	if (split && prev->lineno - prev->offset >= prev->height) {

		int lines = prev->lineno - prev->offset - prev->height + 1;


		do_scroll_view(prev, lines);
	}

	if (prev && view != prev && split && view_is_displayed(prev)) {

		update_view_title(prev);
	}

	if (view->pipe && view->lines == 0) {


		werase(view->win);
		view->p_restore = flags & (OPEN_RELOAD | OPEN_REFRESH);
		report("");
	} else if (view_is_displayed(view)) {
		redraw_view(view);
		report("");
	}
}
