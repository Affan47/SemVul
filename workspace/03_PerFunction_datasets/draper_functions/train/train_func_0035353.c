on_frame_arrow_clicked(CellRendererFrameIcon *cell_renderer, gchar *path, gpointer user_data)
{
    GtkTreePath *new_active_frame = gtk_tree_path_new_from_string (path);
    if (gtk_tree_path_get_indices(new_active_frame)[1] != active_frame_index)
	{
		GtkTreeIter iter;

		GtkTreeRowReference *reference = (GtkTreeRowReference*)g_hash_table_lookup(threads, (gpointer)active_thread_id);
		GtkTreePath *old_active_frame = gtk_tree_row_reference_get_path(reference);
		gtk_tree_path_append_index(old_active_frame, active_frame_index);

		gtk_tree_model_get_iter(model, &iter, old_active_frame);
		gtk_tree_store_set (store, &iter, S_ACTIVE, FALSE, -1);

		active_frame_index = gtk_tree_path_get_indices(new_active_frame)[1];
		select_frame(active_frame_index);

		gtk_tree_model_get_iter(model, &iter, new_active_frame);
		gtk_tree_store_set (store, &iter, S_ACTIVE, TRUE, -1);

		gtk_tree_path_free(old_active_frame);
	}

	gtk_tree_path_free(new_active_frame);
}
