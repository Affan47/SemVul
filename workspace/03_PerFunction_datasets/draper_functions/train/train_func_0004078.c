delete_step_records (struct job_record *job_ptr)
{
	ListIterator step_iterator;
	struct step_record *step_ptr;

	xassert(job_ptr);
	step_iterator = list_iterator_create (job_ptr->step_list);

	last_job_update = time(NULL);
	while ((step_ptr = (struct step_record *) list_next (step_iterator))) {
		list_remove (step_iterator);
		_free_step_rec(step_ptr);
	}

	list_iterator_destroy (step_iterator);
}
