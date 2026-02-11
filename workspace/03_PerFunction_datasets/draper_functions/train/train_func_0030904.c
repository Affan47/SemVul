miner_web_finalize (GObject *object)
{
	TrackerMinerWebPrivate *priv;

	priv = TRACKER_MINER_WEB_GET_PRIVATE (object);

	if (priv->registration_id != 0) {
		g_dbus_connection_unregister_object (tracker_miner_get_dbus_connection (TRACKER_MINER (object)),
		                                     priv->registration_id);
	}

	if (priv->introspection_data) {
		g_dbus_node_info_unref (priv->introspection_data);
	}

	G_OBJECT_CLASS (tracker_miner_web_parent_class)->finalize (object);
}
