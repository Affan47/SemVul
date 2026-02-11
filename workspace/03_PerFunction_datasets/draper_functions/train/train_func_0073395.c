config_init(void)
{
	config_file = g_build_filename(geany->app->configdir, "plugins", "geanydoc", NULL);
	utils_mkdir(config_file, TRUE);

	setptr(config_file, g_build_filename(config_file, "geanydoc.conf", NULL));

	config = g_key_file_new();
	if (!g_key_file_load_from_file(config, config_file, G_KEY_FILE_KEEP_COMMENTS, NULL))
	{
		g_key_file_load_from_data(config, defaults, sizeof(defaults),
					  G_KEY_FILE_KEEP_COMMENTS, NULL);
	}
}
