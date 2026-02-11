server_setup_remove_config(SERVER_SETUP_REC *rec)
{
	CONFIG_NODE *node;
	int index;

	node = iconfig_node_traverse("servers", FALSE);
	if (node != NULL) {
		index = g_slist_index(setupservers, rec);
		iconfig_node_list_remove(node, index);
	}
}
