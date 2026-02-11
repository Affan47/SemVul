tree_view_cursor_changed_cb(GtkWidget *widget, gpointer data)
{
	int *row;
	preset *ps;
	gint pos;
	GtkTreePath *path = NULL;
	GtkTreeViewColumn *focus_column = NULL;

	if (settings.presets == NULL)
		return;

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(tree_view), &path, &focus_column);

	if (path == NULL)
		return;

	row = gtk_tree_path_get_indices(path);
	g_assert(row);

	mom_ps = *row;
	preset_combo_set_item(mom_ps);

	ps = g_list_nth_data(settings.presets, *row);
	g_assert(ps);

	pos = g_list_index(settings.presets, (gpointer)ps);

	if (pos == 0)
		gtk_widget_set_sensitive(move_up_button, FALSE);
	else
		gtk_widget_set_sensitive(move_up_button, TRUE);

	if (pos + 1 == gtk_tree_model_iter_n_children(GTK_TREE_MODEL(list_store), NULL))
		gtk_widget_set_sensitive(move_down_button, FALSE);
	else
		gtk_widget_set_sensitive(move_down_button, TRUE);

	gtk_tree_path_free(path);
	return;
}
