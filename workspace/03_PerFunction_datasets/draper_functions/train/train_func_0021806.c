alloc_simple_node_pos(struct rooted_tree *t)
{
	struct list_elem *le;
	struct rnode *node;

	for (le = t->nodes_in_order->head; NULL != le; le = le->next) {
		node = le->data;
		node->data = malloc(sizeof(struct simple_node_pos));
		if (NULL == node->data) return FAILURE;
	}
	return SUCCESS;
}
