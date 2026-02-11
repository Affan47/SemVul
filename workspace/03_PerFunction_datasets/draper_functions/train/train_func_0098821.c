_dessert_agentx_init_subagent() {


	pthread_t snmp_worker;

	snmp_enable_calllog();


	debug_register_tokens(AGENT);


	debug_register_tokens("dessertAppParamsTable");
	debug_register_tokens("verbose:dessertAppParamsTable");
	debug_register_tokens("internal:dessertAppParamsTable");

	debug_register_tokens("dessertAppParamsTable");
	debug_register_tokens("verbose:dessertAppStatsTable");
	debug_register_tokens("internal:dessertAppStatsTable");

	snmp_set_do_debugging(1);

	netsnmp_log_handler *logh;

	logh = netsnmp_register_loghandler(NETSNMP_LOGHANDLER_FILE, LOG_DEBUG);
	if (logh) {
		logh->pri_max = LOG_EMERG;
		logh->token = strdup("/tmp/dessertAGENTX.log");
	}

	netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_ROLE, 1);


	init_agent(AGENT);


	init_dessertObjects();


	init_dessertMeshifTable();
	init_dessertSysifTable();


	init_dessertAppParamsTable();
	init_dessertAppStatsTable();

	init_snmp(AGENT);
	DEBUGMSGTL((AGENT, "Initialized agent and snmp.\n"));

	pthread_create(&snmp_worker, NULL, _dessert_agentx_worker, NULL);
}
