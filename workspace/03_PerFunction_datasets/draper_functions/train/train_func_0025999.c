set_property (GObject *object, guint prop_id,
              const GValue *value, GParamSpec *pspec)
{
	NMVPNPluginPrivate *priv = NM_VPN_PLUGIN_GET_PRIVATE (object);

	switch (prop_id) {
	case PROP_DBUS_SERVICE_NAME:

		priv->dbus_service_name = g_strdup (g_value_get_string (value));
		break;
	case PROP_STATE:
		nm_vpn_plugin_set_state (NM_VPN_PLUGIN (object),
		                         (NMVPNServiceState) g_value_get_uint (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
