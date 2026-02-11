selected_items_table_foreach (gchar *path, gpointer status,
                              StatusSelectionData *data)
{
	if (GPOINTER_TO_INT (status) & data->status_codes)
		data->list = g_list_append (data->list, g_strdup (path));
}
