search_ancestry_by_name (GladeWidget *toplevel, const gchar *name)
{
	GladeWidget *widget = NULL, *iter;
	GList *list, *children;

	if ((children = glade_widget_get_children (toplevel)) != NULL)
	{
		for (list = children; list; list = list->next)
		{
			iter = glade_widget_get_from_gobject (list->data);

			if (iter->name && strcmp (iter->name, name) == 0)
			{
				widget = iter;
				break;
			}
			else if ((widget = search_ancestry_by_name (iter, name)) != NULL)
				break;
		}

		g_list_free (children);
	}
	return widget;
}
