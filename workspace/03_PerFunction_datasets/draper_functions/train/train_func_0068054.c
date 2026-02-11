gda_connection_event_finalize (GObject *object)
{
	GdaConnectionEvent *event = (GdaConnectionEvent *) object;

	g_return_if_fail (GDA_IS_CONNECTION_EVENT (event));


	if (event->priv->description)
		g_free (event->priv->description);
	if (event->priv->source)
		g_free (event->priv->source);
	if (event->priv->sqlstate)
		g_free (event->priv->sqlstate);

	g_free (event->priv);
	event->priv = NULL;


	parent_class->finalize (object);
}
