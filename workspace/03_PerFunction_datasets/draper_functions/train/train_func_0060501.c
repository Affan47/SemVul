step_epilog_complete(struct job_record  *job_ptr,
		char *node_name)
{
	int rc = 0, node_inx, step_offset;
	ListIterator step_iterator;
	struct step_record *step_ptr;
	struct node_record *node_ptr;

	if (!switch_g_part_comp()) {

		return 0;
	}
	if ((node_ptr = find_node_record(node_name)) == NULL)
		return 0;
	node_inx = node_ptr - node_record_table_ptr;

	step_iterator = list_iterator_create(job_ptr->step_list);
	while ((step_ptr = (struct step_record *) list_next (step_iterator))) {
		if (step_ptr->state != JOB_RUNNING)
			continue;
		if ((!step_ptr->switch_job)
		||  (bit_test(step_ptr->step_node_bitmap, node_inx) == 0))
			continue;
		if (step_ptr->exit_node_bitmap) {
			step_offset = _step_hostname_to_inx(
					step_ptr, node_name);
			if ((step_offset < 0)
			||  bit_test(step_ptr->exit_node_bitmap,
					step_offset))
				continue;
			bit_set(step_ptr->exit_node_bitmap,
				step_offset);
		}
		rc++;
		debug2("partitial switch release for step %u.%u, "
			"epilog on %s", job_ptr->job_id,
			step_ptr->step_id, node_name);
		switch_g_job_step_part_comp(
			step_ptr->switch_job, node_name);
	}
	list_iterator_destroy (step_iterator);

	return rc;
}
