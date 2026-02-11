cal_client_view_dispose (GObject *object)
{
	ECalClientViewPrivate *priv;

	priv = E_CAL_CLIENT_VIEW_GET_PRIVATE (object);

	g_weak_ref_set (&priv->client, NULL);

	if (priv->connection != NULL) {
		g_object_unref (priv->connection);
		priv->connection = NULL;
	}

	if (priv->main_context != NULL) {
		g_main_context_unref (priv->main_context);
		priv->main_context = NULL;
	}

	if (priv->dbus_proxy != NULL) {
		g_signal_handler_disconnect (
			priv->dbus_proxy,
			priv->objects_added_handler_id);
		g_signal_handler_disconnect (
			priv->dbus_proxy,
			priv->objects_modified_handler_id);
		g_signal_handler_disconnect (
			priv->dbus_proxy,
			priv->objects_removed_handler_id);
		g_signal_handler_disconnect (
			priv->dbus_proxy,
			priv->progress_handler_id);
		g_signal_handler_disconnect (
			priv->dbus_proxy,
			priv->complete_handler_id);


		e_gdbus_cal_view_call_dispose (
			priv->dbus_proxy, NULL,
			cal_client_view_dispose_cb, NULL);
		g_object_unref (priv->dbus_proxy);
		priv->dbus_proxy = NULL;
	}


	G_OBJECT_CLASS (e_cal_client_view_parent_class)->dispose (object);
}
