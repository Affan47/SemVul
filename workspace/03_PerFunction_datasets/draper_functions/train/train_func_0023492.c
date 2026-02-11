trigger_node_up(struct node_record *node_ptr)
{
	int inx = node_ptr - node_record_table_ptr;

	slurm_mutex_lock(&trigger_mutex);
	if (trigger_up_nodes_bitmap == NULL)
		trigger_up_nodes_bitmap = bit_alloc(node_record_count);
	bit_set(trigger_up_nodes_bitmap, inx);
	slurm_mutex_unlock(&trigger_mutex);
}
