cb_sheet_export_toggled (G_GNUC_UNUSED GtkCellRendererToggle *cell,
			 const gchar *path_string,
			 TextExportState *state)
{
	GtkTreePath *path = gtk_tree_path_new_from_string (path_string);
	GtkTreeIter  iter;
	gboolean value;

	if (gtk_tree_model_get_iter (GTK_TREE_MODEL (state->sheets.model),
				     &iter, path)) {
		gtk_tree_model_get
			(GTK_TREE_MODEL (state->sheets.model), &iter,
			 STF_EXPORT_COL_EXPORTED,	&value,
			 -1);
		gtk_list_store_set
			(state->sheets.model, &iter,
			 STF_EXPORT_COL_EXPORTED,	!value,
			 -1);
		set_sheet_selection_count
			(state,
			 state->sheets.num_selected + (value ? -1 : 1));
	} else {
		g_warning ("Did not get a valid iterator");
	}
	gtk_tree_path_free (path);
}
