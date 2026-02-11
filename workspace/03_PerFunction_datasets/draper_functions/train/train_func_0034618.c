get_visible_provider (GtkSourceCompletion *completion)
{
	GList *visible = gtk_source_completion_model_get_visible_providers (completion->priv->model_proposals);

	if (visible != NULL)
	{
		return GTK_SOURCE_COMPLETION_PROVIDER (visible->data);
	}
	else
	{
		return NULL;
	}
}
