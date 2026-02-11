snippets_provider_unload (SnippetsProvider *snippets_provider)
{
	SnippetsProviderPrivate *priv = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPETS_PROVIDER (snippets_provider));
	priv = ANJUTA_SNIPPETS_PROVIDER_GET_PRIVATE (snippets_provider);


	if (!IANJUTA_IS_EDITOR_ASSIST (priv->editor_assist))
		return;


	ianjuta_editor_assist_remove (priv->editor_assist,
	                              IANJUTA_PROVIDER (snippets_provider),
	                              NULL);
	priv->editor_assist = NULL;


	stop_listening (snippets_provider);

}
