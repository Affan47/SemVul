get_property (GObject *object, guint prop_id,
		    GValue *value, GParamSpec *pspec)
{
	NMSettingIP6ConfigPrivate *priv = NM_SETTING_IP6_CONFIG_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_METHOD:
		g_value_set_string (value, priv->method);
		break;
	case PROP_DNS:
		nm_utils_ip6_dns_to_gvalue (priv->dns, value);
		break;
	case PROP_DNS_SEARCH:
		g_value_set_boxed (value, priv->dns_search);
		break;
	case PROP_ADDRESSES:
		nm_utils_ip6_addresses_to_gvalue (priv->addresses, value);
		break;
	case PROP_ROUTES:
		nm_utils_ip6_routes_to_gvalue (priv->routes, value);
		break;
	case PROP_IGNORE_AUTO_ROUTES:
		g_value_set_boolean (value, priv->ignore_auto_routes);
		break;
	case PROP_IGNORE_AUTO_DNS:
		g_value_set_boolean (value, priv->ignore_auto_dns);
		break;
	case PROP_DHCP_HOSTNAME:
		g_value_set_string (value, priv->dhcp_hostname);
		break;
	case PROP_NEVER_DEFAULT:
		g_value_set_boolean (value, priv->never_default);
		break;
	case PROP_MAY_FAIL:
		g_value_set_boolean (value, priv->may_fail);
		break;
	case PROP_IP6_PRIVACY:
		g_value_set_int (value, priv->ip6_privacy);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
