tracker_config_file_migrate (TrackerConfigFile           *file,
                             GSettings                   *settings,
                             TrackerConfigMigrationEntry *entries)
{
	g_return_val_if_fail (TRACKER_IS_CONFIG_FILE (file), FALSE);

	if (G_UNLIKELY (g_getenv ("TRACKER_USE_CONFIG_FILES"))) {
		UnappliedNotifyData *data;

#ifdef CONFIG_ENABLE_TRACE
		g_message ("Using config file, not GSettings");
#endif


		if (!file->file_exists) {
			migrate_settings_to_keyfile (entries,
			                             settings,
			                             file);
			tracker_config_file_save (file);
		}


		data = g_new (UnappliedNotifyData, 1);
		data->file = g_object_ref (file);
		data->entries = entries;

		g_signal_connect (settings, "notify::has-unapplied",
		                  G_CALLBACK (settings_has_unapplied_notify),
		                  data);
	} else {

#ifdef CONFIG_ENABLE_TRACE
		g_message ("Using GSettings, not config file");
#endif
		tracker_config_file_import_to_settings (file, settings, entries);


#ifdef CONFIG_ENABLE_TRACE
		g_message ("  Removing old config file");
#endif
		g_file_delete (file->file, NULL, NULL);
	}

	return TRUE;
}
