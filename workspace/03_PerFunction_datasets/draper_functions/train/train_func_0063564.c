_throttle_start(int *active_rpc_cnt)
{
	slurm_mutex_lock(&throttle_mutex);
	while (1) {
		if (*active_rpc_cnt == 0) {
			(*active_rpc_cnt)++;
			break;
		}
		pthread_cond_wait(&throttle_cond, &throttle_mutex);
	}
	slurm_mutex_unlock(&throttle_mutex);
	usleep(1);
}
