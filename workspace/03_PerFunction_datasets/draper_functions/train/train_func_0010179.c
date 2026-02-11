_other_node_ops(node_op_t type)
{
	unsigned i;

	for (i = 0; i < NUM_NODES; i++)
		if (type != i && _count_node_ops[i])
			return 1;
	return 0;
}
