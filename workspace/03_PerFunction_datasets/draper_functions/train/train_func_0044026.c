on_config_page_select (GtkTreeSelection *selection, gpointer user_data)
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected (selection, &model, &iter))
	{
		gchar *tmp = gtk_tree_model_get_string_from_iter (model, &iter);
		gtk_notebook_set_current_page (GTK_NOTEBOOK(user_data), atoi((const char *)tmp));
	}
}
