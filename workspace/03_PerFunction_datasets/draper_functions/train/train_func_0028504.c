j_add_agent(char *name, char *alias, char *desc, char *service, char *host,
	char *agent_type)
{
	Agent *agent = g_new0(Agent, 1);

	eb_debug(DBG_JBR, "Agent %s[%s]: %s [%s] [%s]\n",
		host, name, alias, desc, service);
	if (!host) {
		g_warning("No host specified for service, not registering!");
		g_free(agent);
		return;
	}
	strncpy(agent->host, host, 256);
	if (agent_type)
		strncpy(agent->type, agent_type, 256);
	if (name)
		strncpy(agent->name, name, 256);
	if (alias)
		strncpy(agent->alias, alias, 256);
	if (desc)
		strncpy(agent->desc, desc, 256);
	if (service)
		strncpy(agent->service, service, 256);

	agent_list = g_list_append(agent_list, agent);
	return;
}
