request_oob_method(DBusConnection *dbus_conn,
					DBusMessage *message, void *user_data)
{
	DBusMessageIter iter;

	DBG("");

	dbus_message_iter_init(message, &iter);

	if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_ARRAY)
		return get_reply_on_error(message, EINVAL);

	return create_request_oob_reply(message);
}
