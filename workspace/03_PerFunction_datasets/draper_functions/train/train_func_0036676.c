fm_tree_view_trash_cb (GtkWidget *menu_item,
		       FMTreeView *view)
{
	GList *list;

	if (!nemo_file_can_trash (view->details->popup_file)) {
		return;
	}

	list = g_list_prepend (NULL,
			       nemo_file_get_location (view->details->popup_file));

	nemo_file_operations_trash_or_delete (list,
						  fm_tree_view_get_containing_window (view),
						  NULL, NULL);
	g_list_free_full (list, g_object_unref);
}
