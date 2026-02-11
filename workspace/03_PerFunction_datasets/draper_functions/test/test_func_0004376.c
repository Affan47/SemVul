open_uri(const gchar * uri)
{
	int result;
	gchar *command;
	GError *error = NULL;
#ifdef WIN32
	gchar *browser_command =
		cfg_get_single_value_as_string_with_default(config, "Misc", "browser-win32", "cmd /c start %s");
#else
#ifdef OSX
	gchar *browser_command = cfg_get_single_value_as_string_with_default(config, "Misc", "browser-osx", "open '%s'");
#else
	gchar *browser_command = cfg_get_single_value_as_string_with_default(config, "Misc", "browser", "xdg-open '%s'");
#endif
#endif
	gchar *escaped_uri = g_strdup(uri);
	command = g_strdup_printf(browser_command, escaped_uri);
	g_free(escaped_uri);
	result = g_spawn_command_line_async(command, &error);
	if (error)
	{

		gchar *str = g_markup_printf_escaped("%s: '%s': %s", _("Failed to execute"), command, error->message);
		playlist3_show_error_message(str, ERROR_WARNING);
		g_free(str);
		g_error_free(error);
		error = NULL;
	}
	g_free(browser_command);
	g_free(command);
}
