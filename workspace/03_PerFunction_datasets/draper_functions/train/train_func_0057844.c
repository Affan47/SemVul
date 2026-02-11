account_list_view_select_account(GtkWidget *list_view, gint account_id)
{
	FindAccountInStore fis;
	GtkTreeModel *model;

	fis.account_id = account_id;
	fis.path = NULL;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(list_view));

	gtk_tree_model_foreach(model, (GtkTreeModelForeachFunc) find_account_in_store,
			       &fis);

	if (fis.path) {
		GtkTreeSelection *selection;
		GtkTreePath* path;

		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_view));
		gtk_tree_selection_select_iter(selection, &fis.iter);
		path = gtk_tree_model_get_path(model, &fis.iter);

		gtk_tree_view_set_cursor(GTK_TREE_VIEW(list_view), path, NULL, FALSE);
		gtk_tree_path_free(path);
	}

	return fis.path != NULL;
}
