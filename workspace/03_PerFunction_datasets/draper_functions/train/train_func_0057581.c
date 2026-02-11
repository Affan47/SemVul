que_node_get_containing_loop_node(

	que_node_t*	node)
{
	ut_ad(node);

	for (;;) {
		ulint	type;

		node = que_node_get_parent(node);

		if (!node) {
			break;
		}

		type = que_node_get_type(node);

		if ((type == QUE_NODE_FOR) || (type == QUE_NODE_WHILE)) {
			break;
		}
	}

	return(node);
}
