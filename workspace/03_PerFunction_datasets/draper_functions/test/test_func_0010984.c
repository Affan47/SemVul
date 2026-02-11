autoresponder_plugin_init(int prio)
{
	PLUGIN_CHECK_VER("autoresponder");

	plugin_register(&autoresponder_plugin, prio);

	query_connect_id(&autoresponder_plugin, PROTOCOL_MESSAGE, autoresponder_message, NULL);
	variable_add(&autoresponder_plugin, "allowed_sessions", VAR_STR, 1, &config_autoresponder_allowed_sessions, NULL, NULL, NULL);
	variable_add(&autoresponder_plugin, "answer", VAR_STR, 1, &config_autoresponder_answer, autoresponder_varchange, NULL, NULL);
	variable_add(&autoresponder_plugin, "greeting", VAR_STR, 1, &config_autoresponder_greeting, NULL, NULL, NULL);
	variable_add(&autoresponder_plugin, "match_mode", VAR_INT, 1, &config_autoresponder_match_mode, autoresponder_varchange,
			variable_map(3, 0, 0, "exact", 1, 2, "substring", 2, 1, "regex"), NULL);
	variable_add(&autoresponder_plugin, "question", VAR_STR, 1, &config_autoresponder_question, NULL, NULL, NULL);

	return 0;
}
