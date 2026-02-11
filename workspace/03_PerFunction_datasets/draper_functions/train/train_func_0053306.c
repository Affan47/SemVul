isns_create_node(const char *iname)
{
	isns_source_t *source;
	struct isns_node_list *node;

	source = isns_source_create_iscsi(iname);
	if (!source)
		return NULL;

	node = calloc(1, sizeof(*node));
	if (!node) {
		isns_source_release(source);
		return NULL;
	}
	INIT_LIST_HEAD(&node->list);
	node->source = source;
	return node;
}
