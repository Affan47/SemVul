register_endpoint(DBusConnection *conn, DBusMessage *msg,
					void *data)
{
	struct media_adapter *adapter = data;
	DBusMessageIter args, props;
	const char *sender, *path, *uuid;
	gboolean delay_reporting = FALSE;
	uint8_t codec;
	uint8_t *capabilities;
	int size = 0;
	int err;

	sender = dbus_message_get_sender(msg);

	dbus_message_iter_init(msg, &args);

	dbus_message_iter_get_basic(&args, &path);
	dbus_message_iter_next(&args);

	if (media_adapter_find_endpoint(adapter, sender, path, NULL) != NULL)
		return btd_error_already_exists(msg);

	dbus_message_iter_recurse(&args, &props);
	if (dbus_message_iter_get_arg_type(&props) != DBUS_TYPE_DICT_ENTRY)
		return btd_error_invalid_args(msg);

	if (parse_properties(&props, &uuid, &delay_reporting, &codec,
						&capabilities, &size) < 0)
		return btd_error_invalid_args(msg);

	if (media_endpoint_create(adapter, sender, path, uuid, delay_reporting,
				codec, capabilities, size, &err) == NULL) {
		if (err == -EPROTONOSUPPORT)
			return btd_error_not_supported(msg);
		else
			return btd_error_invalid_args(msg);
	}

	return g_dbus_create_reply(msg, DBUS_TYPE_INVALID);
}
