nemo_monitor_directory (GFile *location)
{
	GFileMonitor *dir_monitor;
	NemoMonitor *ret;

	dir_monitor = g_file_monitor_directory (location, G_FILE_MONITOR_WATCH_MOUNTS, NULL, NULL);

	ret = g_new0 (NemoMonitor, 1);
	ret->monitor = dir_monitor;

	if (ret->monitor) {
		g_signal_connect (ret->monitor, "changed", (GCallback)dir_changed, ret);
	}


	return ret;
}
