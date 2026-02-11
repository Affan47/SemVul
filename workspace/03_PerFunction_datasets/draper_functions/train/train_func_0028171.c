config_node_first(GSList *list)
{
	while (list != NULL) {
		CONFIG_NODE *node = list->data;

		if (node->type != NODE_TYPE_COMMENT)
                        break;
		list = list->next;
	}
	return list;
}
