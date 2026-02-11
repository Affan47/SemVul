sap_manager_init(DBusConnection *conn)
{
	connection = dbus_connection_ref(conn);

	if (sap_server_init(connection) < 0) {
		error("Can't init SAP server");
		dbus_connection_unref(conn);
		return -1;
	}

	btd_register_adapter_driver(&sap_server_driver);

	return 0;
}
