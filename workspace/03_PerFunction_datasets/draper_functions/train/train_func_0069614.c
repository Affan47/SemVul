dbus_init()
{
	g_log_set_handler(NULL, G_LOG_LEVEL_MASK, my_log_handler, NULL);
	g_type_init();
	g_log_set_always_fatal(G_LOG_LEVEL_WARNING);
	GError* g_err = NULL;
	g_conn = dbus_g_bus_get(DBUS_BUS_SYSTEM, &g_err);
	if (g_err != NULL)
	{

		LOG(LOG_ERR, "Connecting to system bus failed: %s", g_err->message);
		g_error_free(g_err);
		return -1;
	}
	GObject* obj = (GObject*)muxer_control_gen();
	DBusError err;
	memset(&err, 0, sizeof(err));
	if (dbus_bus_request_name(dbus_g_connection_get_connection(g_conn), "org.pyneo.muxer", DBUS_NAME_FLAG_ALLOW_REPLACEMENT|DBUS_NAME_FLAG_REPLACE_EXISTING, &err) < 0)
	{
		if (dbus_error_is_set(&err))
			LOG(LOG_ERR, "dbus error with dbus_bus_request_name '%s' '%s'", err.name, err.message);
		else
			LOG(LOG_ERR, "dbus error with dbus_bus_request_name");
		return -1;
	}
	dbus_g_object_type_install_info(TYPE_MUXER_CONTROL, &dbus_glib_mux_object_info);
	dbus_g_connection_register_g_object(g_conn, object_name, obj);
	return 0;
}
