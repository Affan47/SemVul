get_mm_enabled_done (DBusGProxy *proxy, DBusGProxyCall *call_id, gpointer user_data)
{
	NMModem *self = NM_MODEM (user_data);
	GError *error = NULL;
	GValue value = { 0, };

	if (!dbus_g_proxy_end_call (proxy, call_id, &error,
	                            G_TYPE_VALUE, &value,
	                            G_TYPE_INVALID)) {
		nm_log_warn (LOGD_MB, "failed get modem enabled state: (%d) %s",
		             error ? error->code : -1,
		             error && error->message ? error->message : "(unknown)");
		return;
	}

	if (G_VALUE_HOLDS_BOOLEAN (&value)) {
		update_mm_enabled (self, g_value_get_boolean (&value));
	} else
		nm_log_warn (LOGD_MB, "failed get modem enabled state: unexpected reply type");

	g_value_unset (&value);
}
