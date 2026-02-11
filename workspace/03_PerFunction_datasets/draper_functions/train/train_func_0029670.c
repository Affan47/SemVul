print_jobs_array(job_info_t * jobs, int size, List format)
{
	int i = 0;
	List l;
	node_info_msg_t *ni = NULL;

	l = list_create(NULL);
	if (!params.no_header)
		print_job_from_format(NULL, format);


	for (; i < size; i++) {
		if (_filter_job(&jobs[i]))
			continue;
		list_append(l, (void *) &jobs[i]);
	}
	sort_jobs_by_start_time (l);
	if (ni)
		slurm_free_node_info_msg (ni);

	sort_job_list (l);


	list_for_each (l, (ListForF) print_job_from_format, (void *) format);
	list_destroy (l);

	return SLURM_SUCCESS;
}
