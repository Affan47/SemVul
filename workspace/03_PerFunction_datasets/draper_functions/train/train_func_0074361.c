get_nodes_in_order(struct rnode *root)
{
	struct rnode_iterator *it = create_rnode_iterator(root);
	if (NULL == it) return NULL;
	struct rnode *current;
	struct llist *traversal = create_llist();
	if (NULL == traversal) return NULL;
	struct llist *reverse_traversal;
	struct llist *nodes_in_reverse_order = create_llist();
	if (NULL == nodes_in_reverse_order) return NULL;
	struct llist *nodes_in_order;


	while ((current = rnode_iterator_next(it)) != NULL) {
		current->seen = 0;
		if (! append_element (traversal, current)) return NULL;
	}

	destroy_rnode_iterator(it);

	reverse_traversal = llist_reverse(traversal);
	if (NULL == reverse_traversal) return NULL;
	destroy_llist(traversal);


	struct list_elem *el;
	for (el = reverse_traversal->head; NULL != el; el = el->next) {
		current = el->data;


		if (current->seen == 0) {

			if (! append_element
					(nodes_in_reverse_order, current))
				return NULL;
			current->seen = 1;
		}
	}

	destroy_llist(reverse_traversal);
	nodes_in_order = llist_reverse(nodes_in_reverse_order);
	if (NULL == nodes_in_order) return NULL;
	destroy_llist(nodes_in_reverse_order);


	for (el = nodes_in_order->head; NULL != el; el = el->next) {
		current = el->data;
		current->seen = 0;
	}
	return nodes_in_order;
}
