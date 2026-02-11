jobacct_gather_startpoll(uint16_t frequency)
{
	int retval = SLURM_SUCCESS;
	pthread_attr_t attr;
	pthread_t _watch_tasks_thread_id;

	if (!plugin_polling)
		return SLURM_SUCCESS;

	if (jobacct_gather_init() < 0)
		return SLURM_ERROR;

	if (!jobacct_shutdown) {
		error("jobacct_gather_startpoll: poll already started!");
		return retval;
	}

	jobacct_shutdown = false;

	freq = frequency;

	task_list = list_create(jobacctinfo_destroy);
	if (frequency == 0) {
		debug2("jobacct_gather dynamic logging disabled");
		return retval;
	}


	slurm_attr_init(&attr);
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
		error("pthread_attr_setdetachstate error %m");

	if  (pthread_create(&_watch_tasks_thread_id, &attr,
			    &_watch_tasks, NULL)) {
		debug("jobacct_gather failed to create _watch_tasks "
		      "thread: %m");
		frequency = 0;
	} else
		debug3("jobacct_gather dynamic logging enabled");
	slurm_attr_destroy(&attr);

	return retval;
}
