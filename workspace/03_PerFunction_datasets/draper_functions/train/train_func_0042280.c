media_item2_dbus_interface_get_property (GDBusConnection* connection, const gchar* sender, const gchar* object_path, const gchar* interface_name, const gchar* property_name, GError** error, gpointer user_data) {
	gpointer* data;
	gpointer object;
	data = user_data;
	object = data[0];
	if (strcmp (property_name, "URLs") == 0) {
		return _dbus_media_item2_get_URLs (object);
	} else if (strcmp (property_name, "MIMEType") == 0) {
		return _dbus_media_item2_get_MIMEType (object);
	}
	return NULL;
}
