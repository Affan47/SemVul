on_snippets_view_selection_changed (GtkTreeSelection *tree_selection,
                                    gpointer user_data)
{
	SnippetsBrowser *snippets_browser = NULL;
	SnippetsBrowserPrivate *priv = NULL;
	GtkTreeIter iter;
	GObject *cur_object = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPETS_BROWSER (user_data));
	snippets_browser = ANJUTA_SNIPPETS_BROWSER (user_data);
	priv = ANJUTA_SNIPPETS_BROWSER_GET_PRIVATE (snippets_browser);
	g_return_if_fail (GTK_IS_TREE_MODEL (priv->filter));

	if (!gtk_tree_selection_get_selected (tree_selection, &priv->filter, &iter))
	{
		snippets_editor_set_snippet (priv->snippets_editor, NULL);
		return;
	}

	gtk_tree_model_get (priv->filter, &iter,
	                    SNIPPETS_DB_MODEL_COL_CUR_OBJECT, &cur_object,
	                    -1);


	if (ANJUTA_IS_SNIPPET (cur_object) && priv->maximized)
		snippets_editor_set_snippet (priv->snippets_editor,
		                             ANJUTA_SNIPPET (cur_object));
	else if (priv->maximized)
		snippets_editor_set_snippet (priv->snippets_editor, NULL);

	g_object_unref (cur_object);
}
