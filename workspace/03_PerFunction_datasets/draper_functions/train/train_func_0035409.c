preview_selected_items (NautilusListView *view)
{
	GList *file_list;

	file_list = nautilus_list_view_get_selection (NAUTILUS_VIEW (view));

	if (file_list != NULL) {
		nautilus_view_preview_files (NAUTILUS_VIEW (view),
					     file_list, NULL);
		nautilus_file_list_free (file_list);
	}
}
