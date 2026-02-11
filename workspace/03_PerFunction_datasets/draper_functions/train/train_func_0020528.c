custom_attr_window_add_attr(void)
{
	gchar *new_attr = gtk_editable_get_chars(GTK_EDITABLE(custom_attr_window.add_entry),
								0, -1);
	g_strstrip(new_attr);
	if (new_attr && *new_attr) {
		GtkListStore *list_store = GTK_LIST_STORE(gtk_tree_view_get_model
						(GTK_TREE_VIEW(custom_attr_window.attr_list)));
		FindAttrInStore fis;

		fis.attr = new_attr;
		fis.path = NULL;
		gtk_tree_model_foreach(gtk_tree_view_get_model
				(GTK_TREE_VIEW(custom_attr_window.attr_list)),
				(GtkTreeModelForeachFunc) find_attr_in_store,
				&fis);

		if (fis.path) {

			GtkTreeSelection *selection;
			GtkTreePath* path;
			GtkTreeModel *model = gtk_tree_view_get_model(
				GTK_TREE_VIEW(custom_attr_window.attr_list));

			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(custom_attr_window.attr_list));
			gtk_tree_selection_select_iter(selection, &fis.iter);

			path = gtk_tree_model_get_path(model, &fis.iter);

			gtk_tree_view_set_cursor(GTK_TREE_VIEW(custom_attr_window.attr_list),
						path, NULL, FALSE);

			gtk_list_store_set(list_store, &fis.iter,
						CUSTOM_ATTR_NAME, new_attr,
						-1);

			gtk_tree_path_free(path);
		} else {

			GtkTreeIter iter;

			gtk_list_store_append(list_store, &iter);
			gtk_list_store_set(list_store, &iter,
					   CUSTOM_ATTR_NAME, new_attr,
					   -1);
		}
		dirty = TRUE;
	} else {
		alertpanel_error(_("Attribute name is not set."));
	}
	g_free(new_attr);
}
