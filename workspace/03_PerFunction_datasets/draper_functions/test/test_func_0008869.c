fm10k_dbg_q_vector_exit(struct fm10k_q_vector *q_vector)
{
	struct fm10k_intfc *interface = q_vector->interface;

	if (interface->dbg_intfc)
		debugfs_remove_recursive(q_vector->dbg_q_vector);
	q_vector->dbg_q_vector = NULL;
}
