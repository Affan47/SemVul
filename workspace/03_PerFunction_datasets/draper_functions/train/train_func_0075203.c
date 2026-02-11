_re_wake(void)
{
	struct node_record *node_ptr;
	bitstr_t *wake_node_bitmap = NULL;
	int i;

	node_ptr = node_record_table_ptr;
	for (i=0; i<node_record_count; i++, node_ptr++) {
		if (IS_NODE_ALLOCATED(node_ptr)   &&
		    IS_NODE_NO_RESPOND(node_ptr)  &&
		    !IS_NODE_POWER_SAVE(node_ptr) &&
		    (bit_test(suspend_node_bitmap, i) == 0)) {
			if (wake_node_bitmap == NULL) {
				wake_node_bitmap =
					bit_alloc(node_record_count);
			}
			bit_set(wake_node_bitmap, i);
		}
	}

	if (wake_node_bitmap) {
		char *nodes;
		nodes = bitmap2node_name(wake_node_bitmap);
		if (nodes) {
			info("power_save: rewaking nodes %s", nodes);
			_run_prog(resume_prog, nodes);
		} else
			error("power_save: bitmap2nodename");
		xfree(nodes);
		FREE_NULL_BITMAP(wake_node_bitmap);
	}
}
