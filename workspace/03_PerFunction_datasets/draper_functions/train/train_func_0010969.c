sel_reset_aggregate_vals(

	sel_node_t*	node)
{
	func_node_t*	func_node;

	ut_ad(node->is_aggregate);

	func_node = node->select_list;

	while (func_node) {
		eval_node_set_int_val(func_node, 0);

		func_node = que_node_get_next(func_node);
	}

	node->aggregate_already_fetched = FALSE;
}
