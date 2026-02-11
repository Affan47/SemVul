gfire_game_config_get_command(const gfire_game_configuration *p_gconf, const gfire_game_data *p_game_data)
{
	if (!p_gconf)
	{
		purple_debug_error("gfire", "Invalid game config info.\n");
		return NULL;
	}

	const gfire_game *game = gfire_game_by_id(p_gconf->game_id);
	if(!game)
	{
		purple_debug_error("gfire", "gfire_game_config_get_command: Game not existing.\n");
		return NULL;
	}

	if (!game->detection_sets || !((gfire_game_detection_set*)game->detection_sets->data)->launch_args ||
		!p_gconf->launch_file)
	{
		purple_debug_error("gfire", "Insufficient information available!\n");
		return NULL;
	}


	gfire_game_detection_set *dset = (gfire_game_detection_set*)game->detection_sets->data;

	gchar *username_args = NULL;


	gchar *password_args = NULL;


	gchar *tmp, *tmp2;
	gchar *network_args = NULL;

	if(dset->network_args && p_game_data && p_game_data->ip.value)
	{
		gchar *server_ip_tmp = NULL, *server_port_tmp = NULL, *tmp = NULL, *tmp2 = NULL;

		server_port_tmp = gfire_game_data_port_str(p_game_data);
		server_ip_tmp = gfire_game_data_ip_str(p_game_data);


		tmp = purple_strreplace(dset->network_args, "%UA_GAME_HOST_NAME%", server_ip_tmp);
		tmp2 = purple_strreplace(tmp, "%UA_GAME_HOST_PORT%", server_port_tmp);
		g_free(tmp);
		g_free(server_port_tmp);
		g_free(server_ip_tmp);


		tmp = purple_strreplace(tmp2, "%UA_LAUNCHER_USERNAME_ARGS%", username_args ? username_args : "");
		g_free(tmp2);


		network_args = purple_strreplace(tmp, "%UA_LAUNCHER_PASSWORD_ARGS%", password_args ? password_args : "");
		g_free(tmp);
	}
	g_free(username_args);
	g_free(password_args);

	gchar *exe;

#ifdef _WIN32
	exe = g_strdup_printf("\"%s\"", p_gconf->launch_file);
#else

	exe = g_strdup_printf("%s \"%s\"", gfire_filetype_use_wine(p_gconf->launch_file) ? "wine": "", p_gconf->launch_file);
#endif

	tmp = purple_strreplace(dset->launch_args, "%UA_LAUNCHER_EXE_PATH%", exe);
	g_free(exe);

	tmp2 = purple_strreplace(tmp, "%UA_LAUNCHER_EXTRA_ARGS%", "");
	g_free(tmp);

	gchar *launch_cmd = purple_strreplace(tmp2, "%UA_LAUNCHER_NETWORK_ARGS%", network_args ? network_args : "");
	g_free(network_args);
	g_free(tmp2);

	return launch_cmd;
}
