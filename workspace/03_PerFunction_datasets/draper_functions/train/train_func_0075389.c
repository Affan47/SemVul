keyconfig_save(const char *id, const char *key, const char *data)
{
	CONFIG_NODE *node;

	g_return_if_fail(id != NULL);
	g_return_if_fail(key != NULL);

	node = key_config_find(key);
	if (node == NULL) {
		node = iconfig_node_traverse("(keyboard", TRUE);
		node = config_node_section(node, NULL, NODE_TYPE_BLOCK);
	}

	iconfig_node_set_str(node, "key", key);
	iconfig_node_set_str(node, "id", id);
	iconfig_node_set_str(node, "data", data);
}
