add_global_variables (SnippetVarsStore *vars_store)
{
	SnippetVarsStorePrivate *priv = NULL;
	GtkTreeIter iter, iter_to_add;
	gchar *cur_var_name = NULL;
	GtkTreeModel *global_vars_model = NULL;
	gchar *instant_value = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPET_VARS_STORE (vars_store));
	priv = ANJUTA_SNIPPET_VARS_STORE_GET_PRIVATE (vars_store);
	global_vars_model = snippets_db_get_global_vars_model (priv->snippets_db);
	g_return_if_fail (GTK_IS_TREE_MODEL (global_vars_model));

	if (gtk_tree_model_get_iter_first (global_vars_model, &iter))
	{
		do
		{
			gtk_tree_model_get (global_vars_model, &iter,
			                    GLOBAL_VARS_MODEL_COL_NAME, &cur_var_name,
			                    -1);


			if (snippet_has_variable (priv->snippet, cur_var_name))
			{
				g_free (cur_var_name);
				continue;
			}
			instant_value = snippets_db_get_global_variable (priv->snippets_db, cur_var_name);

			gtk_list_store_append (GTK_LIST_STORE (vars_store), &iter_to_add);
			gtk_list_store_set (GTK_LIST_STORE (vars_store), &iter_to_add,
					            VARS_STORE_COL_NAME, cur_var_name,
					            VARS_STORE_COL_TYPE, SNIPPET_VAR_TYPE_GLOBAL,
					            VARS_STORE_COL_DEFAULT_VALUE, g_strdup (""),
					            VARS_STORE_COL_INSTANT_VALUE, instant_value,
					            VARS_STORE_COL_IN_SNIPPET, FALSE,
					            VARS_STORE_COL_UNDEFINED, FALSE,
					            -1);

			g_free (cur_var_name);
			g_free (instant_value);

		} while (gtk_tree_model_iter_next (global_vars_model, &iter));
	}
}
