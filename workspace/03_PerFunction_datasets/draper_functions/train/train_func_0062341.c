set_property (GObject *object, guint prop_id,
			  const GValue *value, GParamSpec *pspec)
{
	NMDHCPClientPrivate *priv = NM_DHCP_CLIENT_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_IFACE:

		priv->iface = g_strdup (g_value_get_string (value));
		break;
	case PROP_HWADDR:

		priv->hwaddr = g_value_dup_boxed (value);
		break;
	case PROP_IPV6:

		priv->ipv6 = g_value_get_boolean (value);
		break;
	case PROP_UUID:

		priv->uuid = g_value_dup_string (value);
		break;
	case PROP_TIMEOUT:
		priv->timeout = g_value_get_uint (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
