sms_plugin_init(int prio)
{
	PLUGIN_CHECK_VER("sms");

	plugin_register(&sms_plugin, prio);

	command_add(&sms_plugin, ("sms:sms"), ("u ?"), sms_command_sms, 0, NULL);

	variable_add(&sms_plugin, ("sms_send_app"), VAR_STR, 1, &config_sms_app, NULL, NULL, NULL);
	variable_add(&sms_plugin, ("sms_away"), VAR_MAP, 1, &config_sms_away, NULL, variable_map(3, 0, 0, "none", 1, 2, "all", 2, 1, "separate"), dd_sms);
	variable_add(&sms_plugin, ("sms_away_limit"), VAR_INT, 1, &config_sms_away_limit, NULL, NULL, dd_sms);
	variable_add(&sms_plugin, ("sms_max_length"), VAR_INT, 1, &config_sms_max_length, NULL, NULL, dd_sms);
	variable_add(&sms_plugin, ("sms_number"), VAR_STR, 1, &config_sms_number, NULL, NULL, dd_sms);

	query_connect_id(&sms_plugin, PROTOCOL_MESSAGE, sms_protocol_message, NULL);
	query_connect_id(&sms_plugin, SESSION_STATUS, sms_session_status, NULL);

	return 0;
}
