audio_init(void)
{
	GKeyFile *config;
	gboolean enable_sco;

	connection = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);
	if (connection == NULL)
		return -EIO;

	config = load_config_file(CONFIGDIR "/audio.conf");

	if (audio_manager_init(connection, config, &enable_sco) < 0)
		goto failed;

	if (!enable_sco)
		return 0;

	sco_server = bt_io_listen(BT_IO_SCO, sco_server_cb, NULL, NULL,
					NULL, NULL,
					BT_IO_OPT_INVALID);
	if (!sco_server) {
		error("Unable to start SCO server socket");
		goto failed;
	}

	return 0;

failed:
	audio_manager_exit();

	if (connection) {
		dbus_connection_unref(connection);
		connection = NULL;
	}

	return -EIO;
}
