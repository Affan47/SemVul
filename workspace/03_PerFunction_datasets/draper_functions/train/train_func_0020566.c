cli_current (cli_infos_t *infos, command_context_t *ctx)
{
	const gchar *format;
	gint refresh;

	if (!command_flag_int_get (ctx, "refresh", &refresh)) {
		refresh = 0;
	}

	if (!command_flag_string_get (ctx, "format", &format)) {
		format = configuration_get_string (infos->config, "STATUS_FORMAT");
	}

	status_mode (infos, format, refresh);

	return TRUE;
}
