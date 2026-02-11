get_permissions_reply (DBusGProxy *proxy,
                       DBusGProxyCall *call,
                       gpointer user_data)
{
	NMClient *self = NM_CLIENT (user_data);
	GHashTable *permissions;
	GError *error = NULL;

	dbus_g_proxy_end_call (proxy, call, &error,
	                       DBUS_TYPE_G_MAP_OF_STRING, &permissions,
	                       G_TYPE_INVALID);
	NM_CLIENT_GET_PRIVATE (self)->perm_call = NULL;
	update_permissions (NM_CLIENT (user_data), error ? NULL : permissions);
	g_clear_error (&error);
}
