free_smartphone_preferences_sync_dbus_interface_method_call (GDBusConnection* connection, const gchar* sender, const gchar* object_path, const gchar* interface_name, const gchar* method_name, GVariant* parameters, GDBusMethodInvocation* invocation, gpointer user_data) {
	gpointer* data;
	gpointer object;
	data = user_data;
	object = data[0];
	if (strcmp (method_name, "GetServices") == 0) {
		_dbus_free_smartphone_preferences_sync_get_services (object, parameters, invocation);
	} else if (strcmp (method_name, "GetService") == 0) {
		_dbus_free_smartphone_preferences_sync_get_service (object, parameters, invocation);
	} else if (strcmp (method_name, "GetProfiles") == 0) {
		_dbus_free_smartphone_preferences_sync_get_profiles (object, parameters, invocation);
	} else if (strcmp (method_name, "GetProfile") == 0) {
		_dbus_free_smartphone_preferences_sync_get_profile (object, parameters, invocation);
	} else if (strcmp (method_name, "SetProfile") == 0) {
		_dbus_free_smartphone_preferences_sync_set_profile (object, parameters, invocation);
	} else {
		g_object_unref (invocation);
	}
}
