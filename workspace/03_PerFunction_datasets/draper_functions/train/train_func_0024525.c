scroll_view(struct view *view, enum request request)
{
	int lines = 1;

	assert(view_is_displayed(view));

	switch (request) {
	case REQ_SCROLL_PAGE_DOWN:
		lines = view->height;
	case REQ_SCROLL_LINE_DOWN:
		if (view->offset + lines > view->lines)
			lines = view->lines - view->offset;

		if (lines == 0 || view->offset + view->height >= view->lines) {
			report("Cannot scroll beyond the last line");
			return;
		}
		break;

	case REQ_SCROLL_PAGE_UP:
		lines = view->height;
	case REQ_SCROLL_LINE_UP:
		if (lines > view->offset)
			lines = view->offset;

		if (lines == 0) {
			report("Cannot scroll beyond the first line");
			return;
		}

		lines = -lines;
		break;

	default:
		die("request %d not handled in switch", request);
	}

	do_scroll_view(view, lines);
}
