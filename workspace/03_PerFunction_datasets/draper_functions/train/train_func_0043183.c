get_selected_folders (GList *selection)
{
	GList *folders;
	GList *l;

	folders = NULL;
	for (l = selection; l != NULL; l = l->next) {
		if (nautilus_file_is_directory (l->data))
			folders = g_list_prepend (folders, nautilus_file_ref (l->data));
	}
	return g_list_reverse (folders);
}
