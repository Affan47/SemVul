_clear_job_resv(slurmctld_resv_t *resv_ptr)
{
	ListIterator job_iterator;
	struct job_record *job_ptr;

	job_iterator = list_iterator_create(job_list);
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (job_ptr->resv_ptr != resv_ptr)
			continue;
		if (!IS_JOB_FINISHED(job_ptr)) {
			info("Job %u linked to defunct reservation %s, "
			     "clearing that reservation",
			     job_ptr->job_id, job_ptr->resv_name);
		}
		job_ptr->resv_id = 0;
		job_ptr->resv_ptr = NULL;
		xfree(job_ptr->resv_name);
	}
	list_iterator_destroy(job_iterator);
}
