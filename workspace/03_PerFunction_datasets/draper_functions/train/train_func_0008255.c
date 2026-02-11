glade_inspector_visible_func (GtkTreeModel* model,
                              GtkTreeIter* parent,
                              gpointer data)
{
	GladeInspector* inspector = data;
	GladeInspectorPrivate *priv = inspector->priv;

	GtkTreeIter iter;

	gboolean retval = FALSE;

	if (priv->search_disabled)
		return TRUE;

	if (gtk_tree_model_iter_children (model, &iter, parent))
	{
		do
		{
			retval = glade_inspector_visible_func (model, &iter, data);
		}
		while (gtk_tree_model_iter_next (model, &iter) && !retval);
	}
	if (!retval)
	{
		const gchar* text = gtk_entry_get_text (GTK_ENTRY(priv->entry));
		gchar* widget_name;

		gtk_tree_model_get (model, parent, GLADE_PROJECT_MODEL_COLUMN_NAME,
		                    &widget_name, -1);

		retval = find_in_string_insensitive (widget_name, text);

		g_free (widget_name);
	}

	return retval;
}
