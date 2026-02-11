_wait_for_thread (pthread_t thread_id)
{
	int i;

	for (i=0; i<20; i++) {
		pthread_cond_broadcast(&comp_list_cond);
		usleep(1000 * i);
		if (pthread_kill(thread_id, 0))
			return SLURM_SUCCESS;
	}

	error("Could not kill jobcomp script pthread");
	return SLURM_ERROR;
}
