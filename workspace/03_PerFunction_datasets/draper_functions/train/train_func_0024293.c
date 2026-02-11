snippet_set_keywords_list (AnjutaSnippet *snippet,
                           const GList *keywords_list)
{
	GList *iter = NULL;
	AnjutaSnippetPrivate *priv = NULL;
	gchar *cur_keyword = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPET (snippet));
	priv = ANJUTA_SNIPPET_GET_PRIVATE (snippet);


	for (iter = g_list_first (priv->keywords); iter != NULL; iter = g_list_next (iter))
	{
		g_free (iter->data);
	}
	g_list_free (g_list_first (priv->keywords));
	priv->keywords = NULL;


	for (iter = g_list_first ((GList *)keywords_list); iter != NULL; iter = g_list_next (iter))
	{
		cur_keyword = g_strdup ((const gchar *)iter->data);
		priv->keywords = g_list_append (priv->keywords, cur_keyword);
	}

}
