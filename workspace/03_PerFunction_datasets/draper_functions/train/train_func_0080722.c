search_gui_append_detail(const gchar *title, const gchar *value)
{
	GtkTreeModel *model;
	GtkTreeView *tv;
	GtkTreeIter iter;

	tv = search_gui_treeview_search_details();
	g_return_if_fail(tv);

	model = gtk_tree_view_get_model(tv);
	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, title, 1, value, (-1));
}
