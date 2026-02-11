update_completion (GtkSourceCompletion        *completion,
                   GList                      *providers,
                   GtkSourceCompletionContext *context)
{
	GList *item;


	GList *providers_copy = g_list_copy (providers);
	GtkSourceCompletionContext *context_copy = g_object_ref_sink (context);


	reset_completion (completion);

	completion->priv->context = context_copy;
	completion->priv->running_providers = g_list_copy (providers_copy);
	completion->priv->active_providers = g_list_copy (providers_copy);


	gtk_tree_view_set_model (completion->priv->tree_view_proposals, NULL);
	gtk_tree_view_columns_autosize (completion->priv->tree_view_proposals);

	replace_model (completion);

	for (item = providers_copy; item != NULL; item = g_list_next (item))
	{
		GtkSourceCompletionProvider *provider = item->data;
		gtk_source_completion_provider_populate (provider, context_copy);
	}

	g_list_free (providers_copy);
}
