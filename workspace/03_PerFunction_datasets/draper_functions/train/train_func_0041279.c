_task_layout_cyclic(slurm_step_layout_t *step_layout,
			       uint16_t *cpus)
{
	int i, j, taskid = 0;
	bool over_subscribe = false;

	for (j=0; taskid<step_layout->task_cnt; j++) {
		bool space_remaining = false;
		for (i=0; ((i<step_layout->node_cnt)
			   && (taskid<step_layout->task_cnt)); i++) {
			if ((j<cpus[i]) || over_subscribe) {
				xrealloc(step_layout->tids[i], sizeof(uint32_t)
					 * (step_layout->tasks[i] + 1));

				step_layout->tids[i][step_layout->tasks[i]] =
					taskid;
				taskid++;
				step_layout->tasks[i]++;
				if ((j+1) < cpus[i])
					space_remaining = true;
			}
		}
		if (!space_remaining)
			over_subscribe = true;
	}
	return SLURM_SUCCESS;
}
