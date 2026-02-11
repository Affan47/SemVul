dbus_util_send_message(const char *signal_name, const char *text)
{
	DBusMessage *message;


	if (NULL == bus)
		return;


	message = dbus_message_new_signal(DBUS_PATH, DBUS_INTERFACE, signal_name);

	if (NULL == message) {
		g_message("could not create D-BUS message!");
	} else {


		dbus_message_append_args(message, DBUS_TYPE_STRING, &text,
								 DBUS_TYPE_INVALID);


		dbus_connection_send(bus, message, NULL);

#if 0
		g_message("Sent D-BUS signal '%s': %s", signal_name, text);
#endif


		dbus_message_unref(message);
    }
}
