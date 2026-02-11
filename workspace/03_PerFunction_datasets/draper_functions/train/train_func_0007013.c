snippet_vars_store_add_variable_to_snippet (SnippetVarsStore *vars_store,
                                            const gchar *variable_name,
                                            gboolean get_global)
{
	SnippetVarsStorePrivate *priv = NULL;
	GtkTreeIter iter;


	g_return_if_fail (ANJUTA_IS_SNIPPET_VARS_STORE (vars_store));
	g_return_if_fail (variable_name != NULL);
	priv = ANJUTA_SNIPPET_VARS_STORE_GET_PRIVATE (vars_store);
	g_return_if_fail (ANJUTA_IS_SNIPPETS_DB (priv->snippets_db));
	g_return_if_fail (ANJUTA_IS_SNIPPET (priv->snippet));


	if (snippet_has_variable (priv->snippet, variable_name))
		return;


	if (get_global)
	{
		if (!get_iter_at_variable (vars_store, &iter, variable_name, SNIPPET_VAR_TYPE_GLOBAL, FALSE))
		{


			gtk_list_store_prepend (GTK_LIST_STORE (vars_store), &iter);
			gtk_list_store_set (GTK_LIST_STORE (vars_store), &iter,
			                    VARS_STORE_COL_NAME, variable_name,
			                    VARS_STORE_COL_TYPE, SNIPPET_VAR_TYPE_GLOBAL,
			                    VARS_STORE_COL_DEFAULT_VALUE, "",
			                    VARS_STORE_COL_INSTANT_VALUE, "",
			                    VARS_STORE_COL_IN_SNIPPET, TRUE,
			                    VARS_STORE_COL_UNDEFINED, TRUE,
			                    -1);
		}
		else
		{
			gtk_list_store_set (GTK_LIST_STORE (vars_store), &iter,
		                        VARS_STORE_COL_IN_SNIPPET, TRUE,
		                        -1);
		}
	}

	else
	{
		gtk_list_store_prepend (GTK_LIST_STORE (vars_store), &iter);
		gtk_list_store_set (GTK_LIST_STORE (vars_store), &iter,
			                VARS_STORE_COL_NAME, variable_name,
			                VARS_STORE_COL_TYPE, SNIPPET_VAR_TYPE_LOCAL,
			                VARS_STORE_COL_DEFAULT_VALUE, "",
			                VARS_STORE_COL_INSTANT_VALUE, "",
			                VARS_STORE_COL_IN_SNIPPET, TRUE,
			                VARS_STORE_COL_UNDEFINED, FALSE,
			                -1);
	}

	snippet_add_variable (priv->snippet, variable_name, "", get_global);
}
