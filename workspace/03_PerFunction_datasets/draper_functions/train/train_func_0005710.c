config_node_find(CONFIG_NODE *node, const char *key)
{
	GSList *tmp;

	g_return_val_if_fail(node != NULL, NULL);
	g_return_val_if_fail(key != NULL, NULL);
	g_return_val_if_fail(is_node_list(node), NULL);

	for (tmp = node->value; tmp != NULL; tmp = tmp->next) {
		CONFIG_NODE *node = tmp->data;

		if (node->key != NULL && g_strcasecmp(node->key, key) == 0)
			return node;
	}

	return NULL;
}
