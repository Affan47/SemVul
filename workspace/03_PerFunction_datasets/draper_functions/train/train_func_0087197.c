purge_old_job(void)
{
	ListIterator job_iterator;
	struct job_record  *job_ptr;
	time_t now = time(NULL);
	int i;

	job_iterator = list_iterator_create(job_list);
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (!IS_JOB_PENDING(job_ptr))
			continue;
		if (test_job_dependency(job_ptr) == 2) {
			info("Job dependency can't be satisfied, cancelling "
			     "job %u", job_ptr->job_id);
			job_ptr->job_state	= JOB_CANCELLED;
			xfree(job_ptr->state_desc);
			job_ptr->start_time	= now;
			job_ptr->end_time	= now;
			job_completion_logger(job_ptr, false);
			last_job_update		= now;
			srun_allocate_abort(job_ptr);
		}
	}
	list_iterator_destroy(job_iterator);

	i = list_delete_all(job_list, &_list_find_job_old, "");
	if (i) {
		debug2("purge_old_job: purged %d old job records", i);

	}
}
