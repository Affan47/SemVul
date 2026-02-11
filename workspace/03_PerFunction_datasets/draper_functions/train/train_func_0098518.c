free_smartphone_audio_manager_sync_register_object (gpointer object, GDBusConnection* connection, const gchar* path, GError** error) {
	guint result;
	gpointer *data;
	data = g_new (gpointer, 3);
	data[0] = g_object_ref (object);
	data[1] = g_object_ref (connection);
	data[2] = g_strdup (path);
	result = g_dbus_connection_register_object (connection, path, (GDBusInterfaceInfo *) (&_free_smartphone_audio_manager_sync_dbus_interface_info), &_free_smartphone_audio_manager_sync_dbus_interface_vtable, data, _free_smartphone_audio_manager_sync_unregister_object, error);
	if (!result) {
		return 0;
	}
	g_signal_connect (object, "mode-changed", (GCallback) _dbus_free_smartphone_audio_manager_sync_mode_changed, data);
	g_signal_connect (object, "device-changed", (GCallback) _dbus_free_smartphone_audio_manager_sync_device_changed, data);
	g_signal_connect (object, "volume-changed", (GCallback) _dbus_free_smartphone_audio_manager_sync_volume_changed, data);
	g_signal_connect (object, "mute-changed", (GCallback) _dbus_free_smartphone_audio_manager_sync_mute_changed, data);
	return result;
}
