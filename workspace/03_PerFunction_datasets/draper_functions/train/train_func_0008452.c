alert_bar_dispose (GObject *object)
{
	EAlertBarPrivate *priv;

	priv = E_ALERT_BAR_GET_PRIVATE (object);

	while (!g_queue_is_empty (&priv->alerts)) {
		EAlert *alert = g_queue_pop_head (&priv->alerts);
		g_signal_handlers_disconnect_by_func (
			alert, alert_bar_response_cb, object);
		g_object_unref (alert);
	}


	G_OBJECT_CLASS (e_alert_bar_parent_class)->dispose (object);
}
