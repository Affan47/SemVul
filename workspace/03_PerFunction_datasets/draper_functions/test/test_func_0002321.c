on_check_column_toggled (GtkCellRendererToggle *cell, gchar *path, gpointer user_data)
{
	GcrListSelector *self = GCR_LIST_SELECTOR (user_data);
	GtkTreeIter iter, model_iter;

	g_assert (path != NULL);

	if (gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL (self->pv->filter), &iter, path)) {
		gtk_tree_model_filter_convert_iter_to_child_iter (self->pv->filter, &model_iter, &iter);
		gcr_collection_model_toggle_selected (self->pv->model, &model_iter);
	}
}
