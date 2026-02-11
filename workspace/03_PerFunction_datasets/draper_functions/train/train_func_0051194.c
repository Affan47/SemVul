_logger_logger_vanished (Logger* self, GDBusConnection* conn, const gchar* name) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (conn != NULL);
	g_return_if_fail (name != NULL);
	_g_object_unref0 (logger__logger);
	logger__logger = NULL;
	_g_object_unref0 (logger__dbus_conn);
	logger__dbus_conn = NULL;
	g_signal_emit_by_name (self, "invalidated");
}
