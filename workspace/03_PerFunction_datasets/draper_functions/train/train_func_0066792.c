kill_metadata_service (void)
{
	if (dbus_connection) {
		if (g_dbus_connection_is_closed (dbus_connection) == FALSE) {
			rb_debug ("closing dbus connection");
			g_dbus_connection_close_sync (dbus_connection, NULL, NULL);
		} else {
			rb_debug ("dbus connection already closed");
		}
		g_object_unref (dbus_connection);
		dbus_connection = NULL;
	}

	if (metadata_child) {
		rb_debug ("killing child process");
		kill (metadata_child, SIGINT);
		g_spawn_close_pid (metadata_child);
		metadata_child = 0;
	}

	if (metadata_stdout != -1) {
		rb_debug ("closing metadata child process stdout pipe");
		close (metadata_stdout);
		metadata_stdout = -1;
	}
}
