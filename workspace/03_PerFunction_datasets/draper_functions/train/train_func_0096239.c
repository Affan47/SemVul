_rebuild_part_name_list(struct job_record  *job_ptr)
{
	bool job_active = false, job_pending = false;
	struct part_record *part_ptr;
	ListIterator part_iterator;

	xfree(job_ptr->partition);
	if (IS_JOB_RUNNING(job_ptr) || IS_JOB_SUSPENDED(job_ptr)) {
		job_active = true;
		xfree(job_ptr->partition);
		job_ptr->partition = xstrdup(job_ptr->part_ptr->name);
	} else if (IS_JOB_PENDING(job_ptr))
		job_pending = true;

	part_iterator = list_iterator_create(job_ptr->part_ptr_list);
	if (part_iterator == NULL)
		fatal("list_iterator_create malloc failure");
	while ((part_ptr = (struct part_record *) list_next(part_iterator))) {
		if (job_pending) {

			job_ptr->part_ptr = part_ptr;
			job_pending = false;
		}
		if (job_active && (part_ptr == job_ptr->part_ptr))
			continue;
		if (job_ptr->partition)
			xstrcat(job_ptr->partition, ",");
		xstrcat(job_ptr->partition, part_ptr->name);
	}
	list_iterator_destroy(part_iterator);
	last_job_update = time(NULL);
}
