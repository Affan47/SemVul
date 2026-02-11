search_gui_metadata_update(const bitzi_data_t *data)
{
	const GList *iter;
	gchar *text;

	text = bitzi_gui_get_metadata(data);


	iter = search_gui_get_searches();
	for (; NULL != iter; iter = g_list_next(iter)) {
		struct result_data *rd;
		search_t *search;

		search = iter->data;
	   	rd = find_parent2(search, data->sha1, data->size);
		if (rd) {
			GtkTreeView *tv = GTK_TREE_VIEW(search->tree);
			atom_str_change(&rd->meta, text ? text : _("Not in database"));
			search_gui_data_changed(gtk_tree_view_get_model(tv), rd);
			if (search_gui_item_is_inspected(rd->record)) {
				search_gui_set_bitzi_metadata(rd->record);
				search_gui_set_details(rd->record);
			}
		}
	}

	HFREE_NULL(text);
}
