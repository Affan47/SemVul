log_request(struct view *view, enum request request, struct line *line)
{
	switch (request) {
	case REQ_REFRESH:
		load_refs();
		open_view(view, REQ_VIEW_LOG, OPEN_REFRESH);
		return REQ_NONE;
	default:
		return pager_request(view, request, line);
	}
}
