activate_selected_items_alternate (NautilusListView *view,
				   NautilusFile *file,
				   gboolean open_in_tab)
{
	GList *file_list;
	NautilusWindowOpenFlags flags;

	flags = 0;

	if (open_in_tab) {
		flags |= NAUTILUS_WINDOW_OPEN_FLAG_NEW_TAB;
	} else {
		flags |= NAUTILUS_WINDOW_OPEN_FLAG_NEW_WINDOW;
	}

	if (file != NULL) {
		nautilus_file_ref (file);
		file_list = g_list_prepend (NULL, file);
	} else {
		file_list = nautilus_list_view_get_selection (NAUTILUS_VIEW (view));
	}
	nautilus_view_activate_files (NAUTILUS_VIEW (view),
				      file_list,
				      flags,
				      TRUE);
	nautilus_file_list_free (file_list);

}
