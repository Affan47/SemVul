gres_plugin_step_test(List step_gres_list, List job_gres_list,
				      int node_offset, bool ignore_alloc,
				      uint32_t job_id, uint32_t step_id)
{
	int i;
	uint32_t cpu_cnt, tmp_cnt;
	ListIterator  job_gres_iter, step_gres_iter;
	gres_state_t *job_gres_ptr, *step_gres_ptr;

	if (step_gres_list == NULL)
		return NO_VAL;
	if (job_gres_list == NULL)
		return 0;

	cpu_cnt = NO_VAL;
	(void) gres_plugin_init();

	slurm_mutex_lock(&gres_context_lock);
	step_gres_iter = list_iterator_create(step_gres_list);
	while ((step_gres_ptr = (gres_state_t *) list_next(step_gres_iter))) {
		job_gres_iter = list_iterator_create(job_gres_list);
		while ((job_gres_ptr = (gres_state_t *)
				list_next(job_gres_iter))) {
			if (step_gres_ptr->plugin_id == job_gres_ptr->plugin_id)
				break;
		}
		list_iterator_destroy(job_gres_iter);
		if (job_gres_ptr == NULL) {

			cpu_cnt = 0;
			break;
		}

		for (i=0; i<gres_context_cnt; i++) {
			if (step_gres_ptr->plugin_id !=
			    gres_context[i].plugin_id)
				continue;
			tmp_cnt = _step_test(step_gres_ptr->gres_data,
					     job_gres_ptr->gres_data,
					     node_offset, ignore_alloc,
					     gres_context[i].gres_name,
					     job_id, step_id);
			if (tmp_cnt != NO_VAL) {
				if (cpu_cnt == NO_VAL)
					cpu_cnt = tmp_cnt;
				else
					cpu_cnt = MIN(tmp_cnt, cpu_cnt);
			}
			break;
		}
		if (cpu_cnt == 0)
			break;
	}
	list_iterator_destroy(step_gres_iter);
	slurm_mutex_unlock(&gres_context_lock);

	return cpu_cnt;
}
