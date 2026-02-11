gog_view_get_view_at_point (GogView *view, double x, double y, GogObject **obj, GogTool **tool)
{
	GogView *pointed_view;
	GSList const *ptr;
	GSList *list;
	GogTool *current_tool;

	g_return_val_if_fail (GOG_IS_VIEW (view), NULL);


	list = g_slist_reverse (g_slist_copy (view->children));
	for (ptr = list; ptr != NULL; ptr = ptr->next) {
		pointed_view = gog_view_get_view_at_point (GOG_VIEW (ptr->data), x, y, obj, tool);
		if (pointed_view != NULL) {
			g_slist_free (list);
			return pointed_view;
		}
	}
	g_slist_free (list);

	if ((current_tool = gog_view_get_tool_at_point (view, x, y, obj))) {
		if (tool != NULL)
			*tool = current_tool;
		return view;
	}

	if (obj && *obj)
		*obj = NULL;
	return NULL;
}
