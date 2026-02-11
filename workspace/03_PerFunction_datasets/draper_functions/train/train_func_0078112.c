change_powered(DBusConnection *conn, const char *path,
							dbus_bool_t powered)
{
	DBusMessage *message;
	DBusMessageIter iter;
	DBusPendingCall *call;

	DBG("");

	if (path == NULL)
		return -EINVAL;

	message = dbus_message_new_method_call(BLUEZ_SERVICE, path,
					BLUEZ_ADAPTER_INTERFACE, SET_PROPERTY);
	if (message == NULL)
		return -ENOMEM;

	dbus_message_set_auto_start(message, FALSE);

	dbus_message_iter_init_append(message, &iter);
	connman_dbus_property_append_basic(&iter, "Powered",
						DBUS_TYPE_BOOLEAN, &powered);

	if (dbus_connection_send_with_reply(conn, message,
						&call, TIMEOUT) == FALSE) {
		connman_error("Failed to change Powered property");
		dbus_message_unref(message);
		return -EINVAL;
	}

	if (call == NULL) {
		connman_error("D-Bus connection not available");
		dbus_message_unref(message);
		return -EINVAL;
	}

	dbus_pending_call_set_notify(call, powered_reply,
					g_strdup(path), g_free);

	dbus_message_unref(message);

	return -EINPROGRESS;
}
