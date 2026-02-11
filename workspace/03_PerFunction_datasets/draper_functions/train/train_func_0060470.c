sig_session_restore(CONFIG_REC *config)
{
	CONFIG_NODE *node;
        GSList *tmp;
        char **pids, **pid;


	node = config_node_traverse(config, "(servers", FALSE);
	if (node != NULL) {
		tmp = config_node_first(node->value);
		for (; tmp != NULL; tmp = config_node_next(tmp))
			session_restore_server(tmp->data);
	}


	pids = g_strsplit(config_node_get_str(config->mainnode, "pids", ""), " ", -1);
	for (pid = pids; *pid != NULL; pid++)
                pidwait_add(atoi(*pid));
        g_strfreev(pids);
}
