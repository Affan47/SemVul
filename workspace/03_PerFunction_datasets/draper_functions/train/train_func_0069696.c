data_editing_started (GtkCellRenderer       *cell,
		      GtkCellEditable       *editable,
		      gchar                 *path,
		      GladeEditorProperty   *eprop)
{
	GladeEPropModelData *eprop_data = GLADE_EPROP_MODEL_DATA (eprop);
	gint                 colnum = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (cell), "column-number"));
	gint                 row;
	GtkTreeIter          iter;

	if (!gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL (eprop_data->store), &iter, path))
		return;

	gtk_tree_model_get (GTK_TREE_MODEL (eprop_data->store), &iter,
			    COLUMN_ROW, &row,
			    -1);

	eprop_data->editing_row    = row;
	eprop_data->editing_column = colnum;
}
