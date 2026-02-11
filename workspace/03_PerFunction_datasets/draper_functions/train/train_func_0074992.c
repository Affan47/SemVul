kill_step_on_node(struct job_record  *job_ptr,
			     struct node_record *node_ptr, bool node_fail)
{
	ListIterator step_iterator;
	struct step_record *step_ptr;
	int found = 0;
	int bit_position;

	if ((job_ptr == NULL) || (node_ptr == NULL))
		return found;

	bit_position = node_ptr - node_record_table_ptr;
	step_iterator = list_iterator_create (job_ptr->step_list);
	while ((step_ptr = (struct step_record *) list_next (step_iterator))) {
		if (bit_test(step_ptr->step_node_bitmap, bit_position) == 0)
			continue;
		if (node_fail && !step_ptr->no_kill)
			srun_step_complete(step_ptr);
		info("killing step %u.%u on node %s",
		     job_ptr->job_id, step_ptr->step_id, node_ptr->name);
		signal_step_tasks_on_node(node_ptr->name, step_ptr, SIGKILL,
					  REQUEST_TERMINATE_TASKS);
		found++;
	}

	list_iterator_destroy (step_iterator);
	return found;
}
