main_request(struct view *view, enum request request, struct line *line)
{
	enum open_flags flags = view_is_displayed(view) ? OPEN_SPLIT : OPEN_DEFAULT;

	switch (request) {
	case REQ_ENTER:
		open_view(view, REQ_VIEW_DIFF, flags);
		break;
	case REQ_REFRESH:
		load_refs();
		open_view(view, REQ_VIEW_MAIN, OPEN_REFRESH);
		break;
	default:
		return request;
	}

	return REQ_NONE;
}
