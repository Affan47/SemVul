custom_attr_window_load_list (GList *list)
{

	GList *cur;
	GtkTreeIter iter;
	GtkListStore *list_store = GTK_LIST_STORE(gtk_tree_view_get_model
					(GTK_TREE_VIEW(custom_attr_window.attr_list)));

	custom_attr_window_list_view_clear_list(custom_attr_window.attr_list, FALSE);

	cur = list;
	while (cur) {
		gtk_list_store_append(list_store, &iter);
		gtk_list_store_set(list_store, &iter,
				   CUSTOM_ATTR_NAME, cur->data,
				   -1);
		cur = cur->next;
	}
}
