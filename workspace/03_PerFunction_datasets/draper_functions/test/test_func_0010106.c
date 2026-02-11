prep_req(enum cm_tdbus_type which,
	 const char *path, const char *interface, const char *method)
{
	DBusMessage *msg;
	if (globals.conn == NULL) {
		switch (which) {
		case cm_tdbus_session:
			globals.conn = dbus_bus_get(DBUS_BUS_SESSION, NULL);
			break;
		case cm_tdbus_system:
			globals.conn = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);
			break;
		}
		if (globals.conn == NULL) {
			printf(_("Error connecting to DBus.\n"));
			printf(_("Please verify that the message bus (D-Bus) service is running.\n"));
			exit(1);
		}
	}
	msg = dbus_message_new_method_call(CM_DBUS_NAME,
					   path, interface, method);
	if (msg == NULL) {
		printf(_("Error creating DBus request message.\n"));
		exit(1);
	}
	return msg;
}
