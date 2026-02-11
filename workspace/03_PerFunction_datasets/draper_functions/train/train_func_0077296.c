gedit_document_set_enable_search_highlighting (GeditDocument *doc,
					       gboolean       enable)
{
	g_return_if_fail (GEDIT_IS_DOCUMENT (doc));

	if (doc->priv->search_context != NULL)
	{
		gtk_source_search_context_set_highlight (doc->priv->search_context,
							 enable);
	}
}
