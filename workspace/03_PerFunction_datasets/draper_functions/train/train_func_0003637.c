geo_visit_leaf(struct rnode *leaf, double prob_node_has_children,
		struct llist *leaves_queue)
{

	if (geo_has_children(prob_node_has_children)) {

		struct rnode *kid1 = create_rnode("kid1", "");
		if (NULL == kid1) return FAILURE;
		struct rnode *kid2 = create_rnode("kid2", "");
		if (NULL == kid2) return FAILURE;
		add_child(leaf, kid1);
		add_child(leaf, kid2);
		if (! append_element(leaves_queue, kid1)) return FAILURE;
		if (! append_element(leaves_queue, kid2)) return FAILURE;
	} else {

	}

	return SUCCESS;
}
