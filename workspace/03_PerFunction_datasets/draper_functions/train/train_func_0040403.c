media_keys_dbus_message (DBusConnection* connection, DBusMessage* message, void* object) {
	DBusHandlerResult result;
	result = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Introspectable", "Introspect")) {
		result = _dbus_media_keys_introspect (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.freedesktop.DBus.Properties", "GetAll")) {
		result = _dbus_media_keys_property_get_all (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.gnome.SettingsDaemon.MediaKeys", "GrabMediaPlayerKeys")) {
		result = _dbus_media_keys_GrabMediaPlayerKeys (object, connection, message);
	} else if (dbus_message_is_method_call (message, "org.gnome.SettingsDaemon.MediaKeys", "ReleaseMediaPlayerKeys")) {
		result = _dbus_media_keys_ReleaseMediaPlayerKeys (object, connection, message);
	}
	if (result == DBUS_HANDLER_RESULT_HANDLED) {
		return result;
	} else {
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
	}
}
