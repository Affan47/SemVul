plugin_init(gchar **error)
{
	gchar *rcpath;

	hook_id = -1;

	if (!check_plugin_version(MAKE_NUMERIC_VERSION(2,9,2,72),
				VERSION_NUMERIC, PLUGIN_NAME, error))
		return -1;

	prefs_set_default(param);
	rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, COMMON_RC, NULL);
	prefs_read_config(param, "Bogofilter", rcpath, NULL);
	g_free(rcpath);

	bogofilter_gtk_init();

	debug_print("Bogofilter plugin loaded\n");

#ifdef USE_PTHREAD
	bogofilter_start_thread();
#endif

	if (config.process_emails) {
		bogofilter_register_hook();
	}

	procmsg_register_spam_learner(bogofilter_learn);
	procmsg_spam_set_folder(config.save_folder, bogofilter_get_spam_folder);

	return 0;

}
