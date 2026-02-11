view_hint_deleting(struct view *view, position_t offset,
			       size_t bytes)
{
	if (view->window && in_view(view, &offset, &bytes))
		window_hint_deleting(view->window, offset, bytes);
}
