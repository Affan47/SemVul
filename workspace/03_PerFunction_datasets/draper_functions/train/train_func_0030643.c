read_settings(void)
{
	int old_autolog = autolog_level;
        int log_file_create_mode;

	autolog_path = settings_get_str("autolog_path");
	autolog_level = !settings_get_bool("autolog") ? 0 :
		settings_get_level("autolog_level");

	if (old_autolog && !autolog_level)
		autologs_close_all();


	if (log_theme_name != NULL)
		signal_remove("print format", (SIGNAL_FUNC) sig_print_format);
	log_theme_name = settings_get_str("log_theme");
	if (*log_theme_name == '\0')
		log_theme_name = NULL;
	else
		signal_add("print format", (SIGNAL_FUNC) sig_print_format);

	log_theme = log_theme_name == NULL ? NULL :
		theme_load(log_theme_name);

	log_file_create_mode = octal2dec(settings_get_int("log_create_mode"));
        log_dir_create_mode = log_file_create_mode;
        if (log_file_create_mode & 0400) log_dir_create_mode |= 0100;
        if (log_file_create_mode & 0040) log_dir_create_mode |= 0010;
        if (log_file_create_mode & 0004) log_dir_create_mode |= 0001;

	if (autolog_ignore_targets != NULL)
		g_strfreev(autolog_ignore_targets);

	autolog_ignore_targets = g_strsplit(settings_get_str("autolog_ignore_targets"), " ", -1);
}
