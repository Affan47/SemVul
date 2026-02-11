nautilus_list_view_bump_zoom_level (NautilusView *view, int zoom_increment)
{
	NautilusListView *list_view;
	gint new_level;

	g_return_if_fail (NAUTILUS_IS_LIST_VIEW (view));

	list_view = NAUTILUS_LIST_VIEW (view);
	new_level = list_view->details->zoom_level + zoom_increment;

	if (new_level >= NAUTILUS_ZOOM_LEVEL_SMALLEST &&
	    new_level <= NAUTILUS_ZOOM_LEVEL_LARGEST) {
		nautilus_list_view_set_zoom_level (list_view, new_level, FALSE);
	}
}
