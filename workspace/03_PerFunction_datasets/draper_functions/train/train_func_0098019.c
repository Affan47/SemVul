set_sensitive (GtkCellLayout *cell_layout,
               GtkCellRenderer *cell,
               GtkTreeModel *tree_model,
               GtkTreeIter *iter,
               gpointer data)
{
	gboolean *adhoc = data;
	gboolean sensitive = TRUE, adhoc_valid = TRUE;

	gtk_tree_model_get (tree_model, iter, S_ADHOC_VALID_COLUMN, &adhoc_valid, -1);
	if (*adhoc && !adhoc_valid)
		sensitive = FALSE;

	g_object_set (cell, "sensitive", sensitive, NULL);
}
