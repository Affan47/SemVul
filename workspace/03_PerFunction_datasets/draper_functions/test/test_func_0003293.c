cd_client_get_property (GObject *object,
			 guint prop_id,
			 GValue *value,
			 GParamSpec *pspec)
{
	CdClient *client;
	client = CD_CLIENT (object);

	switch (prop_id) {
	case PROP_DAEMON_VERSION:
		g_value_set_string (value, client->priv->daemon_version);
		break;
	case PROP_SYSTEM_VENDOR:
		g_value_set_string (value, client->priv->system_vendor);
		break;
	case PROP_SYSTEM_MODEL:
		g_value_set_string (value, client->priv->system_model);
		break;
	case PROP_CONNECTED:
		g_value_set_boolean (value, client->priv->proxy != NULL);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
