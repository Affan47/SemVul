size_combo_is_row_separator (GtkTreeModel *model,
			     GtkTreeIter *iter,
			     G_GNUC_UNUSED gpointer data)
{
	gboolean is_sep;
	char *str;

	gtk_tree_model_get (model, iter, 0, &str, -1);
	is_sep = (strcmp (str, "SEPARATOR") == 0);

	g_free (str);

	return is_sep;
}
