modem_manager_1_poke_cb (GDBusConnection *connection,
                         GAsyncResult *res,
                         NMModemManager *self)
{
	GError *error = NULL;
	GVariant *result;

	result = g_dbus_connection_call_finish (connection, res, &error);
	if (error) {

		if (   !g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_SERVICE_UNKNOWN)
		    && !g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_SPAWN_EXEC_FAILED)
		    && !g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_SPAWN_FORK_FAILED)
		    && !g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_SPAWN_FAILED)
		    && !g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_TIMEOUT)
		    && !g_error_matches (error, G_DBUS_ERROR, G_DBUS_ERROR_SPAWN_SERVICE_NOT_FOUND)) {
			nm_log_dbg (LOGD_MB, "error poking ModemManager: %s", error->message);
		}
		g_error_free (error);


		schedule_modem_manager_1_relaunch (self, MODEM_POKE_INTERVAL);
	} else
		g_variant_unref (result);


	g_object_unref (self);
}
