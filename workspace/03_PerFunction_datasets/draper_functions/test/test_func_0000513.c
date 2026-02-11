updater_subscribe_config (updater_t *updater)
{
	xmmsc_result_t *res;
	const gchar *default_directory;

	g_return_if_fail (updater);
	g_return_if_fail (updater->conn);

	default_directory = g_get_user_special_dir (G_USER_DIRECTORY_MUSIC);

	if (!default_directory) {
		default_directory = "";
	}

	res = xmmsc_config_register_value (updater->conn,
	                                   "mlibupdater.watch_dirs",
	                                   default_directory);

	xmmsc_result_notifier_set (res, updater_config_register, updater);
	xmmsc_result_unref (res);

	res = xmmsc_broadcast_config_value_changed (updater->conn);
	xmmsc_result_notifier_set (res, updater_config_changed, updater);
	xmmsc_result_unref (res);
}
