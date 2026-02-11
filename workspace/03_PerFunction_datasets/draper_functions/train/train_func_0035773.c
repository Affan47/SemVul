main (int argc, char *argv[])
{
	DBusConnection * connection;
	DBusMessage * message;
	dbus_bool_t result;


	connection = dbus_init ();
	if (connection == NULL)
		fatal_error ();

	message = dbus_message_new_signal ("/", NM_DHCP_CLIENT_DBUS_IFACE, "Event");
	if (message == NULL) {
		fprintf (stderr, "Error: Not enough memory to send DHCP Event signal.\n");
		fatal_error ();
	}


	result = build_message (message);
	if (result == FALSE) {
		fprintf (stderr, "Error: Not enough memory to send DHCP Event signal.\n");
		fatal_error ();
	}


	result = dbus_connection_send (connection, message, NULL);
	if (!result) {
		fprintf (stderr, "Error: Could not send send DHCP Event signal.\n");
		fatal_error ();
	}
	dbus_message_unref (message);


	dbus_connection_flush (connection);

	return 0;
}
