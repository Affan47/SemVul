j_remove_agents_from_host(char *host)
{
	Agent *agent = NULL;
	GList *list = agent_list;

	eb_debug(DBG_JBR, "Removing host: %s\n", host);
	while (list) {
		agent = list->data;

		list = list->next;
		if (!strcmp(agent->host, host)) {
			eb_debug(DBG_JBR, "Removing %s\n", agent->alias);
			agent_list = g_list_remove(agent_list, agent);
			g_free(agent);
		}
	}
}
