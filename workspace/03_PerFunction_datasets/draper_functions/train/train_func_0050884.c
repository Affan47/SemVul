stop_snippet_editing_session (SnippetsInteraction *snippets_interaction)
{
	SnippetsInteractionPrivate *priv = NULL;


	g_return_if_fail (ANJUTA_IS_SNIPPETS_INTERACTION (snippets_interaction));
	priv = ANJUTA_SNIPPETS_INTERACTION_GET_PRIVATE (snippets_interaction);

	if (!priv->editing)
		return;


	priv->editing = FALSE;
	priv->changing_values_blocker = FALSE;
	priv->selection_set_blocker = FALSE;
	if (IANJUTA_IS_ITERABLE (priv->cur_sel_start_iter))
		g_object_unref (priv->cur_sel_start_iter);
	priv->cur_sel_start_iter = NULL;


	delete_snippet_editing_info (snippets_interaction);

}
