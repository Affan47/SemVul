get_property (GObject *object, guint prop_id,
		    GValue *value, GParamSpec *pspec)
{
	NMSettingVPN *setting = NM_SETTING_VPN (object);
	NMSettingVPNPrivate *priv = NM_SETTING_VPN_GET_PRIVATE (setting);

	switch (prop_id) {
	case PROP_SERVICE_TYPE:
		g_value_set_string (value, nm_setting_vpn_get_service_type (setting));
		break;
	case PROP_USER_NAME:
		g_value_set_string (value, nm_setting_vpn_get_user_name (setting));
		break;
	case PROP_DATA:
		g_value_set_boxed (value, priv->data);
		break;
	case PROP_SECRETS:
		g_value_set_boxed (value, priv->secrets);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
