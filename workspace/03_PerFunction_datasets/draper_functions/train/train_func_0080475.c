up_qos_item_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	UpQosItem *qos_item = UP_QOS_ITEM (object);

	switch (prop_id) {
	case PROP_UID:
		qos_item->priv->uid = g_value_get_uint (value);
		break;
	case PROP_PID:
		qos_item->priv->pid = g_value_get_uint (value);
		break;
	case PROP_SENDER:
		g_free (qos_item->priv->sender);
		qos_item->priv->sender = g_strdup (g_value_get_string (value));
		break;
	case PROP_CMDLINE:
		g_free (qos_item->priv->cmdline);
		qos_item->priv->cmdline = g_strdup (g_value_get_string (value));
		break;
	case PROP_COOKIE:
		qos_item->priv->cookie = g_value_get_uint (value);
		break;
	case PROP_TIMESPEC:
		qos_item->priv->timespec = g_value_get_uint64 (value);
		break;
	case PROP_PERSISTENT:
		qos_item->priv->persistent = g_value_get_boolean (value);
		break;
	case PROP_TYPE:
		qos_item->priv->type = g_value_get_uint (value);
		break;
	case PROP_VALUE:
		qos_item->priv->value = g_value_get_int (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
