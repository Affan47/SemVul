set_property (GObject *object, guint prop_id,
              const GValue *value, GParamSpec *pspec)
{
	NMModemPrivate *priv = NM_MODEM_GET_PRIVATE (object);

	nm_log_dbg (LOGD_MB, "in %s", __func__);

	switch (prop_id) {
	case PROP_PATH:

		priv->path = g_value_dup_string (value);
		break;
	case PROP_CONTROL_PORT:
		priv->control_port = g_value_dup_string (value);
		break;
	case PROP_DATA_PORT:
		priv->data_port = g_value_dup_string (value);
		break;
	case PROP_UID:

		priv->uid = g_value_dup_string (value);
		break;
	case PROP_IP_METHOD:
		priv->ip_method = g_value_get_uint (value);
		break;
	case PROP_IP_TIMEOUT:
		priv->mm_ip_timeout = g_value_get_uint (value);
		break;
	case PROP_ENABLED:
		priv->mm_enabled = g_value_get_boolean (value);
		break;
	case PROP_CONNECTED:
		priv->mm_connected = g_value_get_boolean (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
