row_prebuild_sel_graph(

	row_prebuilt_t*	prebuilt)

{
	sel_node_t*	node;

	ut_ad(prebuilt && prebuilt->trx);

	if (prebuilt->sel_graph == NULL) {

		node = sel_node_create(prebuilt->heap);

		prebuilt->sel_graph = que_node_get_parent(
			pars_complete_graph_for_exec(node,
						     prebuilt->trx,
						     prebuilt->heap));

		prebuilt->sel_graph->state = QUE_FORK_ACTIVE;
	}
}
