set_property (GObject *object, guint prop_id,
		    const GValue *value, GParamSpec *pspec)
{
	NMSettingIP4Config *setting = NM_SETTING_IP4_CONFIG (object);
	NMSettingIP4ConfigPrivate *priv = NM_SETTING_IP4_CONFIG_GET_PRIVATE (setting);

	switch (prop_id) {
	case PROP_METHOD:
		g_free (priv->method);
		priv->method = g_value_dup_string (value);
		break;
	case PROP_DNS:
		g_array_free (priv->dns, TRUE);
		priv->dns = g_value_dup_boxed (value);
		if (!priv->dns)
			priv->dns = g_array_sized_new (FALSE, TRUE, sizeof (guint32), 3);
		break;
	case PROP_DNS_SEARCH:
		nm_utils_slist_free (priv->dns_search, g_free);
		priv->dns_search = g_value_dup_boxed (value);
		break;
	case PROP_ADDRESSES:
		nm_utils_slist_free (priv->addresses, (GDestroyNotify) nm_ip4_address_unref);
		priv->addresses = nm_utils_ip4_addresses_from_gvalue (value);
		break;
	case PROP_ROUTES:
		nm_utils_slist_free (priv->routes, (GDestroyNotify) nm_ip4_route_unref);
		priv->routes = nm_utils_ip4_routes_from_gvalue (value);
		break;
	case PROP_IGNORE_AUTO_ROUTES:
		priv->ignore_auto_routes = g_value_get_boolean (value);
		break;
	case PROP_IGNORE_AUTO_DNS:
		priv->ignore_auto_dns = g_value_get_boolean (value);
		break;
	case PROP_DHCP_CLIENT_ID:
		g_free (priv->dhcp_client_id);
		priv->dhcp_client_id = g_value_dup_string (value);
		break;
	case PROP_DHCP_SEND_HOSTNAME:
		priv->dhcp_send_hostname = g_value_get_boolean (value);
		break;
	case PROP_DHCP_HOSTNAME:
		g_free (priv->dhcp_hostname);
		priv->dhcp_hostname = g_value_dup_string (value);

		if (priv->dhcp_hostname)
			priv->dhcp_send_hostname = TRUE;
		break;
	case PROP_NEVER_DEFAULT:
		priv->never_default = g_value_get_boolean (value);
		break;
	case PROP_MAY_FAIL:
		priv->may_fail = g_value_get_boolean (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
