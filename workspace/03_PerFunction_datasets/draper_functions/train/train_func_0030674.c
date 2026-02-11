on_type_combo_cell_changed (GtkCellRendererCombo *cell,
                            gchar *path_string,
                            gchar *new_string,
                            gpointer user_data)
{
	SnippetsEditorPrivate *priv = NULL;
	GtkTreePath *path = NULL;
	gchar *name = NULL;
	GtkTreeIter iter;
	SnippetVariableType type;


	g_return_if_fail (ANJUTA_IS_SNIPPETS_EDITOR (user_data));
	priv = ANJUTA_SNIPPETS_EDITOR_GET_PRIVATE (user_data);


	path = gtk_tree_path_new_from_string (path_string);
	gtk_tree_model_get_iter (GTK_TREE_MODEL (priv->vars_store_sorted), &iter, path);
	gtk_tree_path_free (path);
	gtk_tree_model_get (GTK_TREE_MODEL (priv->vars_store_sorted), &iter,
	                    VARS_STORE_COL_NAME, &name,
	                    VARS_STORE_COL_TYPE, &type,
	                    -1);

	if (type == SNIPPET_VAR_TYPE_LOCAL)
		snippet_vars_store_set_variable_type (priv->vars_store, name, SNIPPET_VAR_TYPE_GLOBAL);
	else
		snippet_vars_store_set_variable_type (priv->vars_store, name, SNIPPET_VAR_TYPE_LOCAL);

	focus_on_in_snippet_variable (priv->variables_view,
	                              GTK_TREE_MODEL (priv->vars_store_sorted),
	                              name,
	                              NULL, FALSE);

	g_free (name);
}
