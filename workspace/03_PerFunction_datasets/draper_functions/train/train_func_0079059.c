row_separator_func (GtkTreeModel *model,
		    GtkTreeIter  *iter,
		    gpointer      unused)
{
	gboolean retval;
	gchar *name, *title;

	gtk_tree_model_get (model, iter,
			    CONTEXTS_NAME_COLUMN, &name,
			    CONTEXTS_TITLE_COLUMN, &title,
			    -1);

	retval = !name && !title;

	g_free (name);
	g_free (title);

	return retval;
}
