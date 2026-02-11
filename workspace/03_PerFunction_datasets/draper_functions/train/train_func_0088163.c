_watch_tasks(void *arg)
{
	int type = PROFILE_TASK;


	_task_sleep(1);
	while (!jobacct_shutdown && acct_gather_profile_running) {

		_poll_data();
		slurm_mutex_lock(&acct_gather_profile_timer[type].notify_mutex);
		pthread_cond_wait(
			&acct_gather_profile_timer[type].notify,
			&acct_gather_profile_timer[type].notify_mutex);
		slurm_mutex_unlock(&acct_gather_profile_timer[type].
				   notify_mutex);
	}
	return NULL;
}
