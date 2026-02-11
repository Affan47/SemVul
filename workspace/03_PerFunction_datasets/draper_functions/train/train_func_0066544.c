desktop_monitor_remove (NemoDirectory *directory,
		       gconstpointer client)
{
	NemoDesktopDirectory *desktop;
	MergedMonitor *monitor;

	desktop = NEMO_DESKTOP_DIRECTORY (directory);

	monitor = g_hash_table_lookup (desktop->details->monitors, client);
	if (monitor == NULL) {
		return;
	}

	g_hash_table_remove (desktop->details->monitors, client);
}
