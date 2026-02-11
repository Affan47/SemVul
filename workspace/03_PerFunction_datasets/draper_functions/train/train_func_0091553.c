get_format_from_list (GtkWidget *listview)
{
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	GtkTreeIter iter;

	gedit_debug (DEBUG_PLUGINS);

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (listview));
	g_return_val_if_fail (model != NULL, 0);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (listview));
	g_return_val_if_fail (selection != NULL, 0);

	if (gtk_tree_selection_get_selected (selection, NULL, &iter))
	{
		gint selected_value;

		gtk_tree_model_get (model, &iter, COLUMN_INDEX, &selected_value, -1);

		gedit_debug_message (DEBUG_PLUGINS, "Sel value: %d", selected_value);

		return selected_value;
	}

	g_return_val_if_reached (0);
}
