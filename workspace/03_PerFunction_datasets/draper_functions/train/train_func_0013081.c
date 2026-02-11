giggle_diff_tree_view_get_selection (GiggleDiffTreeView *view)
{
	GtkTreeSelection       *selection;
	GtkTreeModel           *model;
	GtkTreeIter             iter;
	gchar                  *file = NULL;

	g_return_val_if_fail (GIGGLE_IS_DIFF_TREE_VIEW (view), NULL);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (view));

	if (gtk_tree_selection_get_selected (selection, &model, &iter))
		gtk_tree_model_get (model, &iter, COL_PATH, &file, -1);

	return file;
}
