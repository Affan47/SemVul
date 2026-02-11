load_module(void)
{
	if (!(agent_tech.capabilities = ast_format_cap_alloc())) {
		ast_log(LOG_ERROR, "ast_format_cap_alloc_nolock fail.\n");
		return AST_MODULE_LOAD_FAILURE;
	}
	ast_format_cap_add_all(agent_tech.capabilities);

	if (ast_channel_register(&agent_tech)) {
		agent_tech.capabilities = ast_format_cap_destroy(agent_tech.capabilities);
		ast_log(LOG_ERROR, "Unable to register channel class 'Agent'\n");
		return AST_MODULE_LOAD_FAILURE;
	}

	if (!read_agent_config(0)) {
		agent_tech.capabilities = ast_format_cap_destroy(agent_tech.capabilities);
		return AST_MODULE_LOAD_DECLINE;
	}

	ast_register_application_xml(app, login_exec);
	ast_register_application_xml(app3, agentmonitoroutgoing_exec);


	ast_data_register_multiple(agents_data_providers, ARRAY_LEN(agents_data_providers));


	ast_manager_register_xml("Agents", EVENT_FLAG_AGENT, action_agents);
	ast_manager_register_xml("AgentLogoff", EVENT_FLAG_AGENT, action_agent_logoff);


	ast_cli_register_multiple(cli_agents, ARRAY_LEN(cli_agents));


	ast_custom_function_register(&agent_function);

	return AST_MODULE_LOAD_SUCCESS;
}
