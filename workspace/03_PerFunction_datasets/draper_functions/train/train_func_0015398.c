title(struct window *window)
{
	char buff[128];
	struct view *view;
	position_t cursor;

	if (!titles)
		return;
	if (window != active_window)
		return;
	if (!window) {
		titles = display_title(display, NULL);
		return;
	}
	view = window->view;
	snprintf(buff, sizeof buff, "%s%s", view->name,
		 view->text->flags & TEXT_CREATED ? " (new)" :
		 view->text->flags & TEXT_RDONLY ? " (read-only)" :
		 view->text->preserved !=
		    view->text->dirties ? " (unsaved)" : "");
	cursor = locus_get(view, CURSOR);
	if (cursor < 65536) {
		int line = current_line_number(view, cursor);
		int len = strlen(buff);
		snprintf(buff + len, sizeof buff - len - 1,
			 " [%d]", line);
	}
	titles = display_title(display, buff);
}
