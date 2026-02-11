remove_cb (DBusGProxy *proxy, DBusGProxyCall *call_id, gpointer user_data)
{
	CBInfo *info = user_data;
	GError *error = NULL;
	char * zone = NULL;

	if (!dbus_g_proxy_end_call (proxy, call_id, &error,
	                            G_TYPE_STRING, &zone,
	                            G_TYPE_INVALID)) {
		g_assert (error);
		nm_log_warn (LOGD_FIREWALL, "(%s) firewall zone remove failed: (%d) %s",
		             info->iface, error->code, error->message);
	}

	g_free (zone);
	g_clear_error (&error);
}
