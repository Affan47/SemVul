statistic_selection(GtkTreeSelection *treeselection, gpointer user_data)
{
GtkTreeModel *model;
GtkTreeIter iter;
guint key = -1;

	DB( g_print("(statistic) selection\n") );

	if (gtk_tree_selection_get_selected(treeselection, &model, &iter))
	{
		gtk_tree_model_get(model, &iter, LST_STAT_KEY, &key, -1);

	}

	DB( g_print(" - active is %d\n", key) );

	statistic_detail(GTK_WIDGET(gtk_tree_selection_get_tree_view (treeselection)), GINT_TO_POINTER(key));
	statistic_sensitive(GTK_WIDGET(gtk_tree_selection_get_tree_view (treeselection)), NULL);
}
