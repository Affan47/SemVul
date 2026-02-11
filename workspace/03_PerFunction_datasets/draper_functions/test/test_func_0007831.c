get_property (GObject *object, guint prop_id,
              GValue *value, GParamSpec *pspec)
{
	NMDeviceEthernet *self = NM_DEVICE_ETHERNET (object);
	NMDeviceEthernetPrivate *priv = NM_DEVICE_ETHERNET_GET_PRIVATE (self);

	switch (prop_id) {
	case PROP_HW_ADDRESS:
		g_value_take_string (value, nm_utils_hwaddr_ntoa (priv->hw_addr, ARPHRD_ETHER));
		break;
	case PROP_PERM_HW_ADDRESS:
		g_value_take_string (value, nm_utils_hwaddr_ntoa (&priv->perm_hw_addr, ARPHRD_ETHER));
		break;
	case PROP_SPEED:
		g_value_set_uint (value, nm_device_wired_get_speed (NM_DEVICE_WIRED (self)));
		break;
	case PROP_CARRIER:
		g_value_set_boolean (value, nm_device_wired_get_carrier (NM_DEVICE_WIRED (self)));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
