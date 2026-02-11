enumerate_modems_cb (DBusGProxy *proxy, DBusGProxyCall *call, gpointer user_data)
{
	GPtrArray *modems;
	GError *error = NULL;
	int i;

	if (!dbus_g_proxy_end_call (proxy, call, &error,
	                            dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH), &modems,
	                            G_TYPE_INVALID)) {
		g_warning ("%s: failed to enumerate modems: (%d) %s",
		           __func__,
		           error ? error->code : -1,
		           error && error->message ? error->message : "(unknown)");
		g_clear_error (&error);
		return;
	}

	for (i = 0; i < modems->len; i++) {
		char *path = g_ptr_array_index (modems, i);

		modem_added (NULL, path, GEOCLUE_GSMLOC_MM (user_data));
		g_free (path);
	}
	g_ptr_array_free (modems, TRUE);
}
