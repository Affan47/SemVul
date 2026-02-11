impl_settings_add_connection (NMSettings *self,
                              GHashTable *settings,
                              DBusGMethodInvocation *context)
{
	NMConnection *connection;
	GError *error = NULL;

	connection = nm_connection_new_from_hash (settings, &error);
	if (connection) {
		nm_settings_add_connection (self, connection, context, add_cb, NULL);
		g_object_unref (connection);
	} else {
		g_assert (error);
		dbus_g_method_return_error (context, error);
		g_error_free (error);
	}
}
