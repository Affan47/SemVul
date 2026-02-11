window_next(struct view *view)
{
	if (view && view->window)
		activate(view->window->next ? view->window->next : window_list);
}
