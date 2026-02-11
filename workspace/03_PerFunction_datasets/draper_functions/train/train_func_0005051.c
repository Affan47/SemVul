_decrement_thd_count(void)
{
	slurm_mutex_lock(&active_mutex);
	if (active_threads > 0)
		active_threads--;
	pthread_cond_signal(&active_cond);
	slurm_mutex_unlock(&active_mutex);
}
