get_property (GObject *object, guint prop_id,
		    GValue *value, GParamSpec *pspec)
{
	NMSettingIP4Config *setting = NM_SETTING_IP4_CONFIG (object);
	NMSettingIP4ConfigPrivate *priv = NM_SETTING_IP4_CONFIG_GET_PRIVATE (setting);

	switch (prop_id) {
	case PROP_METHOD:
		g_value_set_string (value, nm_setting_ip4_config_get_method (setting));
		break;
	case PROP_DNS:
		g_value_set_boxed (value, priv->dns);
		break;
	case PROP_DNS_SEARCH:
		g_value_set_boxed (value, priv->dns_search);
		break;
	case PROP_ADDRESSES:
		nm_utils_ip4_addresses_to_gvalue (priv->addresses, value);
		break;
	case PROP_ROUTES:
		nm_utils_ip4_routes_to_gvalue (priv->routes, value);
		break;
	case PROP_IGNORE_AUTO_ROUTES:
		g_value_set_boolean (value, nm_setting_ip4_config_get_ignore_auto_routes (setting));
		break;
	case PROP_IGNORE_AUTO_DNS:
		g_value_set_boolean (value, nm_setting_ip4_config_get_ignore_auto_dns (setting));
		break;
	case PROP_DHCP_CLIENT_ID:
		g_value_set_string (value, nm_setting_ip4_config_get_dhcp_client_id (setting));
		break;
	case PROP_DHCP_SEND_HOSTNAME:
		g_value_set_boolean (value, nm_setting_ip4_config_get_dhcp_send_hostname (setting));
		break;
	case PROP_DHCP_HOSTNAME:
		g_value_set_string (value, nm_setting_ip4_config_get_dhcp_hostname (setting));
		break;
	case PROP_NEVER_DEFAULT:
		g_value_set_boolean (value, priv->never_default);
		break;
	case PROP_MAY_FAIL:
		g_value_set_boolean (value, priv->may_fail);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
