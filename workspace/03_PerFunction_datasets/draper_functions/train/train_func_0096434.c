set_property(struct modem_data *modem,
			const char *path, const char *interface,
			const char *property, int type, void *value,
			set_property_cb notify)
{
	DBusMessage *message;
	DBusMessageIter iter;
	struct property_info *info;

	DBG("%s path %s %s.%s", modem->path, path, interface, property);

	if (modem->call_set_property != NULL) {
		DBG("Cancel pending SetProperty");

		dbus_pending_call_cancel(modem->call_set_property);
		modem->call_set_property = NULL;
	}

	message = dbus_message_new_method_call(OFONO_SERVICE, path,
					interface, SET_PROPERTY);
	if (message == NULL)
		return -ENOMEM;

	dbus_message_iter_init_append(message, &iter);
	connman_dbus_property_append_basic(&iter, property, type, value);

	if (dbus_connection_send_with_reply(connection, message,
			&modem->call_set_property, TIMEOUT) == FALSE) {
		connman_error("Failed to change property: %s %s.%s",
				path, interface, property);
		dbus_message_unref(message);
		return -EINVAL;
	}

	if (modem->call_set_property == NULL) {
		connman_error("D-Bus connection not available");
		dbus_message_unref(message);
		return -EINVAL;
	}

	info = g_try_new0(struct property_info, 1);
	if (info == NULL) {
		dbus_message_unref(message);
		return -ENOMEM;
	}

	info->modem = modem;
	info->path = path;
	info->interface = interface;
	info->property = property;
	info->set_property_cb = notify;

	dbus_pending_call_set_notify(modem->call_set_property,
					set_property_reply, info, g_free);

	dbus_message_unref(message);

	return -EINPROGRESS;
}
