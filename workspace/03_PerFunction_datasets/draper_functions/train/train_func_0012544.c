gda_connection_event_set_description (GdaConnectionEvent *event, const gchar *description)
{
	g_return_if_fail (GDA_IS_CONNECTION_EVENT (event));

	if (event->priv->description)
		g_free (event->priv->description);
	if (description)
		event->priv->description = g_strdup (description);
	else
		event->priv->description = NULL;
}
