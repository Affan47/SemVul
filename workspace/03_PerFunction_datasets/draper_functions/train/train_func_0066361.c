gres_plugin_step_alloc(List step_gres_list, List job_gres_list,
				  int node_offset, int cpu_cnt,
				  uint32_t job_id, uint32_t step_id)
{
	int i, rc, rc2;
	ListIterator step_gres_iter,  job_gres_iter;
	gres_state_t *step_gres_ptr, *job_gres_ptr;

	if (step_gres_list == NULL)
		return SLURM_SUCCESS;
	if (job_gres_list == NULL) {
		error("gres_plugin_step_alloc: step allocates gres, but job "
		      "%u has none", job_id);
		return SLURM_ERROR;
	}

	rc = gres_plugin_init();

	slurm_mutex_lock(&gres_context_lock);
	step_gres_iter = list_iterator_create(step_gres_list);
	while ((step_gres_ptr = (gres_state_t *) list_next(step_gres_iter))) {
		for (i=0; i<gres_context_cnt; i++) {
			if (step_gres_ptr->plugin_id ==
			    gres_context[i].plugin_id)
				break;
		}
		if (i >= gres_context_cnt) {
			error("gres: step_alloc, could not find plugin %u for "
			      "step %u.%u",
			      step_gres_ptr->plugin_id, job_id, step_id);
			rc = ESLURM_INVALID_GRES;
			break;
		}

		job_gres_iter = list_iterator_create(job_gres_list);
		while ((job_gres_ptr = (gres_state_t *)
				list_next(job_gres_iter))) {
			if (step_gres_ptr->plugin_id == job_gres_ptr->plugin_id)
				break;
		}
		list_iterator_destroy(job_gres_iter);
		if (job_gres_ptr == NULL) {
			info("gres: job %u lacks gres/%s for step %u",
			     job_id, gres_context[i].gres_name, step_id);
			rc = ESLURM_INVALID_GRES;
			break;
		}

		rc2 = _step_alloc(step_gres_ptr->gres_data,
				  job_gres_ptr->gres_data, node_offset,
				  cpu_cnt, gres_context[i].gres_name, job_id,
				  step_id);
		if (rc2 != SLURM_SUCCESS)
			rc = rc2;
	}
	list_iterator_destroy(step_gres_iter);
	slurm_mutex_unlock(&gres_context_lock);

	return rc;
}
