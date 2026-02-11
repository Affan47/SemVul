snippet_add_variable (AnjutaSnippet *snippet,
                      const gchar *variable_name,
                      const gchar *default_value,
                      gboolean is_global)
{
	AnjutaSnippetPrivate *priv = NULL;
	AnjutaSnippetVariable *added_var = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPET (snippet));
	g_return_if_fail (variable_name != NULL);
	g_return_if_fail (default_value != NULL);
	priv = ANJUTA_SNIPPET_GET_PRIVATE (snippet);


	if (snippet_has_variable (snippet, variable_name))
		return;


	added_var = g_malloc (sizeof (AnjutaSnippetVariable));
	added_var->variable_name      = g_strdup (variable_name);
	added_var->default_value      = g_strdup (default_value);
	added_var->is_global          = is_global;
	added_var->cur_value_len      = 0;
	added_var->relative_positions = g_ptr_array_new ();

	priv->variables = g_list_prepend (priv->variables, added_var);
}
