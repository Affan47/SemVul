get_property (GObject *object,
              guint prop_id,
              GValue *value,
              GParamSpec *pspec)
{
	NMDeviceBt *device = NM_DEVICE_BT (object);

	_nm_object_ensure_inited (NM_OBJECT (object));

	switch (prop_id) {
	case PROP_HW_ADDRESS:
		g_value_set_string (value, nm_device_bt_get_hw_address (device));
		break;
	case PROP_NAME:
		g_value_set_string (value, nm_device_bt_get_name (device));
		break;
	case PROP_BT_CAPABILITIES:
		g_value_set_uint (value, nm_device_bt_get_capabilities (device));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
