add_image_cb (char const *key, GOImage *image, GOImageSelState *state)
{
	GtkTreeIter iter;
	GtkTreePath *path;
	gtk_list_store_append (state->model, &iter);
	gtk_list_store_set (state->model, &iter,
			    0, go_image_get_thumbnail (image),
			    1, go_image_get_name (image),
			    -1);
	path = gtk_tree_model_get_path (GTK_TREE_MODEL (state->model), &iter);
	if (image == *(state->result))
		gtk_icon_view_select_path (state->icon_view, path);
	gtk_tree_path_free (path);
}
