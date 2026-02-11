remove(DBusConnection *conn, DBusMessage *msg, void *data)
{
	const char *path;
	int err;

	dbus_message_get_args(msg, NULL, DBUS_TYPE_OBJECT_PATH, &path,
							DBUS_TYPE_INVALID);

	DBG("conn %p path %s", conn, path);

	err = __vpn_provider_remove(path);
	if (err < 0)
		return __connman_error_failed(msg, -err);

	return g_dbus_create_reply(msg, DBUS_TYPE_INVALID);
}
