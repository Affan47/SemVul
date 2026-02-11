pager_request(struct view *view, enum request request, struct line *line)
{
	int split = 0;

	if (request != REQ_ENTER)
		return request;

	if (line->type == LINE_COMMIT &&
	   (view->type == VIEW_LOG ||
	    view->type == VIEW_PAGER)) {
		open_view(view, REQ_VIEW_DIFF, OPEN_SPLIT);
		split = 1;
	}


	scroll_view(view, REQ_SCROLL_LINE_DOWN);


	if (split)
		update_view_title(view);

	return REQ_NONE;
}
