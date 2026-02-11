build_selection_list_from_gfile_list (GList *gfile_list)
{
	GList *result;
	GList *l;

	result = NULL;
	for (l = gfile_list; l; l = l->next) {
		GFile *file;
		NautilusDragSelectionItem *item;

		file = l->data;

		item = nautilus_drag_selection_item_new ();
		item->uri = g_file_get_uri (file);
		item->file = nautilus_file_get_existing (file);
		item->got_icon_position = FALSE;
		result = g_list_prepend (result, item);
	}

	return g_list_reverse (result);
}
