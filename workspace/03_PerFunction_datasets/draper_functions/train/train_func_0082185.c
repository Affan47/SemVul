setup_monitor(SourceviewIO* sio)
{
	if (sio->monitor != NULL)
		g_object_unref (sio->monitor);
	sio->monitor = g_file_monitor_file (sio->file,
	                                    G_FILE_MONITOR_NONE,
	                                    NULL,
	                                    NULL);
	if (sio->monitor)
	{
		g_signal_connect (sio->monitor, "changed",
		                  G_CALLBACK(on_file_changed), sio);
		g_file_monitor_set_rate_limit (sio->monitor, RATE_LIMIT);
	}
}
