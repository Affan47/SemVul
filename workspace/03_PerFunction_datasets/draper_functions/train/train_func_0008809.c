snippet_set_name (AnjutaSnippet *snippet,
                  const gchar *new_name)
{
	AnjutaSnippetPrivate *priv = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPET (snippet));
	g_return_if_fail (new_name != NULL);
	priv = ANJUTA_SNIPPET_GET_PRIVATE (snippet);

	priv->snippet_name = g_strdup (new_name);
}
