freq_cell_edited_cb(GtkCellRendererText *cellrenderertext, gchar *path_str, gchar *new_val, gpointer user_data)
{
	GtkTreePath *path = NULL;
	GtkTreeIter iter;
	preset *ps;
	int *row;
	double value;
	gchar *freq_str;

	if (sscanf(new_val, "%lf", &value) != 1)
		return;

	if (value < FREQ_MIN) value = FREQ_MIN;
	if (value > FREQ_MAX) value = FREQ_MAX;
	value = rint(value * STEPS) / STEPS;

	freq_str = g_strdup_printf("%.2f", value);

	path = gtk_tree_path_new_from_string(path_str);

	row = gtk_tree_path_get_indices(path);
	g_assert(row);
	g_assert(*row < g_list_length(settings.presets));

	ps = g_list_nth_data(settings.presets, *row);
	g_assert(ps);
	ps->freq = value;

	gtk_adjustment_set_value(adj, value * STEPS);
	mom_ps = *row;
	preset_combo_set_item(mom_ps);

	gtk_tree_model_get_iter(GTK_TREE_MODEL(list_store), &iter, path);
	gtk_list_store_set(GTK_LIST_STORE(list_store), &iter, 1, freq_str, -1);
	g_free(freq_str);
	gtk_tree_path_free(path);
}
