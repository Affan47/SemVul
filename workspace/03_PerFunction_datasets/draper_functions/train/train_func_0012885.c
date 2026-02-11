get_property (GObject *object,
              guint prop_id,
              GValue *value,
              GParamSpec *pspec)
{
	NMDeviceOlpcMesh *device = NM_DEVICE_OLPC_MESH (object);

	_nm_object_ensure_inited (NM_OBJECT (object));

	switch (prop_id) {
	case PROP_HW_ADDRESS:
		g_value_set_string (value, nm_device_olpc_mesh_get_hw_address (device));
		break;
	case PROP_COMPANION:
		g_value_set_object (value, nm_device_olpc_mesh_get_companion (device));
		break;
	case PROP_ACTIVE_CHANNEL:
		g_value_set_uint (value, nm_device_olpc_mesh_get_active_channel (device));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}
