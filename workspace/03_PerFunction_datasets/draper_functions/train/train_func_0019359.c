check_foreach (GtkTreeModel *model,
                         GtkTreePath *path,
                         GtkTreeIter *iter,
                         gpointer data)
{
	gint d, m;
	gtk_tree_model_get(GTK_TREE_MODEL(model), iter, 2, &d, 3, &m, -1);

	if (d == ex_day && m == ex_mon)
		date_exists = TRUE;
	else
		date_exists = FALSE;

	return date_exists;
}
