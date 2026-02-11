nm_client_wwan_set_enabled (NMClient *client, gboolean enabled)
{
	GValue value = {0,};

	g_return_if_fail (NM_IS_CLIENT (client));

	g_value_init (&value, G_TYPE_BOOLEAN);
	g_value_set_boolean (&value, enabled);

	_nm_object_set_property (NM_OBJECT (client),
	                         NM_DBUS_INTERFACE,
	                         "WwanEnabled",
	                         &value);
}
