message_view_on_popup_menu(GtkWidget * treeview, gpointer user_data)
{
	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	GList *glist = gtk_tree_selection_get_selected_rows(selection, NULL);
	message_view_t *view = (message_view_t *) user_data;
	GtkTreePath *path;
	GtkTreeIter iter;
	if (glist == NULL) {
		return FALSE;
	}
	path = g_list_nth_data(glist, 0);
	message_view_store_get_iter(GTK_TREE_MODEL(view->store), &iter, path);
	g_list_foreach(glist, message_view_gtk_tree_path_free, NULL);
	g_list_free(glist);
	message_view_popup_menu(treeview, NULL, view, (seaudit_message_t *) iter.user_data);
	return TRUE;
}
