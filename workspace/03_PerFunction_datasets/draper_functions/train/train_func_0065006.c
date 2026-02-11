emit_property_changed(DBusConnection *conn,
					const char *path,
					const char *interface,
					const char *name,
					int type, void *value)
{
	DBusMessage *signal;
	DBusMessageIter iter;

	signal = dbus_message_new_signal(path, interface, "PropertyChanged");

	if (!signal) {
		error("Unable to allocate new %s.PropertyChanged signal",
				interface);
		return FALSE;
	}

	dbus_message_iter_init_append(signal, &iter);

	dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &name);

	append_variant(&iter, type, value);

	return g_dbus_send_message(conn, signal);
}
