check_job_step_time_limit (struct job_record *job_ptr, time_t now)
{
	ListIterator step_iterator;
	struct step_record *step_ptr;
	uint32_t job_run_mins = 0;

	xassert(job_ptr);

	if (job_ptr->job_state != JOB_RUNNING)
		return;

	step_iterator = list_iterator_create (job_ptr->step_list);
	while ((step_ptr = (struct step_record *) list_next (step_iterator))) {
		if (step_ptr->state != JOB_RUNNING)
			continue;
		if (step_ptr->time_limit == INFINITE ||
		    step_ptr->time_limit == NO_VAL)
			continue;
		job_run_mins = (uint32_t) (((now - step_ptr->start_time) -
				step_ptr->tot_sus_time) / 60);
		if (job_run_mins >= step_ptr->time_limit) {

			info("check_job_step_time_limit: job %u step %u "
				"has timed out (%u)",
				job_ptr->job_id, step_ptr->step_id,
				step_ptr->time_limit);
			_signal_step_timelimit(job_ptr, step_ptr, now);
		}
	}
	list_iterator_destroy (step_iterator);
}
