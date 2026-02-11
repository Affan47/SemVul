set_subscriber_number(DBusConnection *conn,
						DBusMessage *msg,
						void *data)
{
	const char *number;

	if (!dbus_message_get_args(msg, NULL, DBUS_TYPE_STRING, &number,
						DBUS_TYPE_INVALID))
		return btd_error_invalid_args(msg);

	g_free(subscriber_number);
	subscriber_number = g_strdup(number);

	DBG("telephony-dummy: subscriber number set to %s", number);

	return dbus_message_new_method_return(msg);
}
