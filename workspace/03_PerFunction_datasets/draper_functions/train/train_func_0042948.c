configuration_load(void)
{
	gchar *configfile = g_build_filename(app->configdir, "geany.conf", NULL);
	GKeyFile *config = g_key_file_new();

	if (! g_file_test(configfile, G_FILE_TEST_IS_REGULAR))
	{

		geany_debug("No user config file found, trying to use global configuration.");
		SETPTR(configfile, g_build_filename(app->datadir, "geany.conf", NULL));
	}
	g_key_file_load_from_file(config, configfile, G_KEY_FILE_NONE, NULL);
	g_free(configfile);

	load_dialog_prefs(config);
	load_ui_prefs(config);
	project_load_prefs(config);
	configuration_load_session_files(config, TRUE);


	g_signal_emit_by_name(geany_object, "load-settings", config);

	g_key_file_free(config);
	return TRUE;
}
