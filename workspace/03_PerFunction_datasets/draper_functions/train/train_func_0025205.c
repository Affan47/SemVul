get_property (GObject *object, guint prop_id,
			  GValue *value, GParamSpec *pspec)
{
	NMIP4ConfigPrivate *priv = NM_IP4_CONFIG_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_ADDRESSES:
		nm_utils_ip4_addresses_to_gvalue (priv->addresses, value);
		break;
	case PROP_NAMESERVERS:
		g_value_set_boxed (value, priv->nameservers);
		break;
	case PROP_DOMAINS:
		g_value_set_boxed (value, priv->domains);
		break;
	case PROP_ROUTES:
		nm_utils_ip4_routes_to_gvalue (priv->routes, value);
		break;
	case PROP_WINS_SERVERS:
		g_value_set_boxed (value, priv->wins);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
