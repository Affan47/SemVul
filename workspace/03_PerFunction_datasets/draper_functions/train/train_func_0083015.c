dest_dnd_set_data(GtkWidget *view,
			      GdkDragContext *context, GtkSelectionData *selection_data,
			      guint info, guint time, gpointer data)
{
	gchar *path = NULL;
	gchar *uri_text = NULL;
	GList *list = NULL;
	gint length = 0;
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	GtkTreeIter iter;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
	if (!gtk_tree_selection_get_selected(selection, &model, &iter)) return;

	gtk_tree_model_get(model, &iter, 1, &path, -1);
	if (!path) return;

	list = g_list_append(list, path);

	switch (info)
		{
		case TARGET_URI_LIST:
			uri_text = uri_text_from_list(list, &length, FALSE);
			break;
		case TARGET_TEXT_PLAIN:
			uri_text = uri_text_from_list(list, &length, TRUE);
			break;
		}

	string_list_free(list);

	if (!uri_text) return;

	gtk_selection_data_set(selection_data, selection_data->target,
			       8, (guchar *)uri_text, length);
	g_free(uri_text);
}
