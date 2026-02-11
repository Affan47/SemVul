advanced_find_delete_cb(GtkButton *button, AdvancedFindDialog *dialog)
{
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(dialog->tree));
	GtkTreeIter iter;
	GtkTreeModel *model;
	AdvancedFind_ListData *data;
	GtkHex *gh = dialog->parent->gh;

	if (gtk_tree_selection_get_selected(selection, &model, &iter) != TRUE)
		return;

	gtk_tree_model_get(model, &iter, 2, &data, -1);
	gtk_hex_delete_autohighlight(gh, data->auto_highlight);
	if(NULL != data->str)
		g_free(data->str);
	g_free(data);
	gtk_list_store_remove(dialog->list, &iter);
}
