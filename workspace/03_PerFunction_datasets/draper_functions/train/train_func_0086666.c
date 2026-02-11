on_enable_for_file(GtkCellRendererToggle *cell_renderer, gchar *path, gpointer user_data)
{
	GtkTreeIter  iter;
	GtkTreePath *tree_path;
	gboolean current_state;


	if (readonly)
		return;

	tree_path = gtk_tree_path_new_from_string (path);

	gtk_tree_model_get_iter (
		model,
		&iter,
		tree_path);

	current_state = gtk_cell_renderer_toggle_get_active(cell_renderer);


    if(1 == gtk_tree_path_get_depth(tree_path))
    {
		gchar *file;
		gtk_tree_model_get (
			model,
			&iter,
			FILEPATH, &file,
			-1);

		breaks_set_enabled_for_file(file, !current_state);

		g_free(file);
	}

	gtk_tree_path_free(tree_path);
}
