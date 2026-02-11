_cancel_jobs (int filter_cnt)
{
	slurm_attr_init(&attr);
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
		error("pthread_attr_setdetachstate error %m");

	slurm_mutex_init(&num_active_threads_lock);

	if (pthread_cond_init(&num_active_threads_cond, NULL))
		error("pthread_cond_init error %m");

	_cancel_jobs_by_state(JOB_PENDING, filter_cnt);
	_cancel_jobs_by_state(JOB_END, filter_cnt);


	pthread_mutex_lock( &num_active_threads_lock );
	while (num_active_threads > 0) {
		pthread_cond_wait( &num_active_threads_cond,
				   &num_active_threads_lock );
	}
	pthread_mutex_unlock( &num_active_threads_lock );

	slurm_attr_destroy(&attr);
	slurm_mutex_destroy(&num_active_threads_lock);
	if (pthread_cond_destroy(&num_active_threads_cond))
		error("pthread_cond_destroy error %m");
}
