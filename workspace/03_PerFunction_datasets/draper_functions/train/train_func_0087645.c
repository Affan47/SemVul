process_tree(struct rooted_tree *tree, struct parameters params)
{

	struct list_elem *elem;

	for (elem = tree->nodes_in_order->head; NULL != elem; elem = elem->next) {
		struct rnode *current = (struct rnode *) elem->data;
		if (! params.show_branch_lengths) {
			char *length = current->edge_length_as_string;
			length[0] = '\0';
		}
		if (! params.show_inner_labels) {
			if (! is_leaf(current)) {
				char *label = current->label;
				label[0] = '\0';
			}
		}
		if (! params.show_leaf_labels) {
			if (is_leaf(current)) {
				char *label = current->label;
				label[0] = '\0';
			}
		}
	}
}
