_e2_edftdlg_find_selected
	(E2_FileTypeDlgRuntime *rt, GtkTreeIter *iter)
{
	GtkTreeSelection *sel =
		gtk_tree_view_get_selection (GTK_TREE_VIEW (rt->views[rt->currentID]));
	GtkTreeModel *mdl;
	if (rt->currentID == E2_CATPANE)

		return (gtk_tree_selection_get_selected (sel, &mdl, iter));

	gboolean retval;
	GList *items = gtk_tree_selection_get_selected_rows (sel, &mdl);
	if (items != NULL)
	{
		retval = gtk_tree_model_get_iter (mdl, iter, (GtkTreePath *)items->data);
		g_list_foreach (items, (GFunc) gtk_tree_path_free, NULL);
		g_list_free (items);
	}
	else
		retval = FALSE;
	return retval;
}
