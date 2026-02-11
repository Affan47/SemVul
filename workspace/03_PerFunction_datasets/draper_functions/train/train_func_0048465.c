nemo_desktop_directory_init (NemoDesktopDirectory *desktop)
{
	desktop->details = g_new0 (NemoDesktopDirectoryDetails, 1);

	desktop->details->callbacks = g_hash_table_new_full
		(merged_callback_hash, merged_callback_equal,
		 NULL, (GDestroyNotify)merged_callback_destroy);
	desktop->details->monitors = g_hash_table_new_full (NULL, NULL,
							    NULL, (GDestroyNotify)merged_monitor_destroy);

	update_desktop_directory (NEMO_DESKTOP_DIRECTORY (desktop));

	g_signal_connect_swapped (nemo_preferences, "changed::" NEMO_PREFERENCES_DESKTOP_IS_HOME_DIR,
				  G_CALLBACK(desktop_directory_changed_callback),
				  desktop);
}
