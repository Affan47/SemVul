gda_connection_event_set_event_type (GdaConnectionEvent *event, GdaConnectionEventType type)
{
	g_return_if_fail (GDA_IS_CONNECTION_EVENT (event));
	g_return_if_fail (event->priv);

	if (event->priv->type == type)
		return;

	event->priv->type = type;
	if (!event->priv->sqlstate && (event->priv->type == GDA_CONNECTION_EVENT_ERROR))
		gda_connection_event_set_sqlstate (event, GDA_SQLSTATE_GENERAL_ERROR);
	else if (((event->priv->type == GDA_CONNECTION_EVENT_NOTICE) ||
		  (event->priv->type == GDA_CONNECTION_EVENT_COMMAND)) &&
		 event->priv->sqlstate)
		gda_connection_event_set_sqlstate (event, NULL);
}
