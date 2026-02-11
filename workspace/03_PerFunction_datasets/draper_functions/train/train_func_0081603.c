_task_info_destroy(stepd_step_task_info_t *t, uint16_t multi_prog)
{
	slurm_mutex_lock(&t->mutex);
	slurm_mutex_unlock(&t->mutex);
	slurm_mutex_destroy(&t->mutex);
	if (multi_prog) {
		xfree(t->argv);
	}
	xfree(t);
}
