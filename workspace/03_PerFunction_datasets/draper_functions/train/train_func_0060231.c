document_stop_file_monitoring(GeanyDocument *doc)
{
	g_return_if_fail(doc != NULL);

	if (doc->priv->monitor != NULL)
	{
		g_object_unref(doc->priv->monitor);
		doc->priv->monitor = NULL;
	}
}
