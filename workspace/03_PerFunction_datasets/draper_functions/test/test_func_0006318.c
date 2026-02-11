find_device(DBusConnection *conn, const char *adapter,
							const char *address)
{
	DBusMessage *message, *reply;
	DBusError error;
	const char *path;
	char *result = NULL;

	message = dbus_message_new_method_call(BLUEZ_SERVICE, adapter,
					ADAPTER_INTF, "FindDevice");
	if (!message)
		return NULL;

	dbus_message_append_args(message, DBUS_TYPE_STRING, &address,
							DBUS_TYPE_INVALID);

	dbus_error_init(&error);

	reply = dbus_connection_send_with_reply_and_block(conn,
							message, -1, &error);

	dbus_message_unref(message);

	if (!reply) {
		if (dbus_error_is_set(&error) == TRUE) {
			fprintf(stderr, "%s\n", error.message);
			dbus_error_free(&error);
		} else
			fprintf(stderr, "Failed to set property\n");
		return NULL;
	}

	if (dbus_message_get_args(reply, NULL, DBUS_TYPE_OBJECT_PATH, &path,
						DBUS_TYPE_INVALID) == FALSE)
		goto done;

	printf("Using device %s for address %s\n", path, address);

	result = strdup(path);

done:
	dbus_message_unref(reply);

	return result;
}
