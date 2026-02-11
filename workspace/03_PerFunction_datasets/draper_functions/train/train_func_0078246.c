set_powered(DBusConnection *conn, DBusMessage *msg,
				gboolean powered, void *data)
{
	struct btd_adapter *adapter = data;
	uint8_t mode;
	int err;

	if (powered) {
		mode = get_mode(&adapter->bdaddr, "on");
		return set_discoverable(conn, msg, mode == MODE_DISCOVERABLE,
									data);
	}

	mode = MODE_OFF;

	if (mode == adapter->mode) {
		adapter->global_mode = mode;
		return dbus_message_new_method_return(msg);
	}

	err = set_mode(adapter, mode, msg);
	if (err < 0)
		return btd_error_failed(msg, strerror(-err));

	return NULL;
}
