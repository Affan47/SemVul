update_job_nodes_completing(void)
{
	ListIterator job_iterator;
	struct job_record *job_ptr;

	if (!job_list)
		return;

	job_iterator = list_iterator_create(job_list);
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if ((!IS_JOB_COMPLETING(job_ptr)) ||
		    (job_ptr->node_bitmap == NULL))
			continue;
		xfree(job_ptr->nodes_completing);
		if (job_ptr->node_bitmap_cg) {
			job_ptr->nodes_completing =
				bitmap2node_name(job_ptr->node_bitmap_cg);
		} else {
			job_ptr->nodes_completing =
				bitmap2node_name(job_ptr->node_bitmap);
		}
	}
	list_iterator_destroy(job_iterator);
}
