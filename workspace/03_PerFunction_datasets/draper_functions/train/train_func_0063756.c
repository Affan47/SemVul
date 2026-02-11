find_existing_account_mod(GtkTreeModel *model, GtkTreePath *path,
	GtkTreeIter *iter, gpointer data)
{
	gpointer serv;

	GtkTreeSelection *selection =
		gtk_tree_view_get_selection(GTK_TREE_VIEW(account_list));

	gtk_tree_model_get(model, iter, SERVICE_TYPE, &serv, -1);

	if (!gtk_tree_selection_path_is_selected(selection, path)
		&& !strcasecmp(serv, data)
		&& !can_multiaccount(eb_services[get_service_id(data)])) {
		return (service_exists = TRUE);
	}

	return (service_exists = FALSE);
}
