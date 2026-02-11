set_property (GObject *object, guint prop_id,
              const GValue *value, GParamSpec *pspec)
{
	NMSettingBridgePrivate *priv = NM_SETTING_BRIDGE_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_INTERFACE_NAME:
		g_free (priv->interface_name);
		priv->interface_name = g_value_dup_string (value);
		break;
	case PROP_STP:
		priv->stp = g_value_get_boolean (value);
		break;
	case PROP_PRIORITY:
		priv->priority = (guint16) g_value_get_uint (value);
		break;
	case PROP_FORWARD_DELAY:
		priv->forward_delay = (guint16) g_value_get_uint (value);
		break;
	case PROP_HELLO_TIME:
		priv->hello_time = (guint16) g_value_get_uint (value);
		break;
	case PROP_MAX_AGE:
		priv->max_age = (guint16) g_value_get_uint (value);
		break;
	case PROP_AGEING_TIME:
		priv->ageing_time = g_value_get_uint (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
