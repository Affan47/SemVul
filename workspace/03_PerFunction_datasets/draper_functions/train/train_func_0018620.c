_step_dealloc_lps(struct step_record *step_ptr)
{
	struct job_record  *job_ptr = step_ptr->job_ptr;
	job_resources_t *job_resrcs_ptr = job_ptr->job_resrcs;
	int cpus_alloc;
	int i_node, i_first, i_last;
	int job_node_inx = -1, step_node_inx = -1;

	xassert(job_resrcs_ptr);
	xassert(job_resrcs_ptr->cpus);
	xassert(job_resrcs_ptr->cpus_used);

	if (step_ptr->step_layout == NULL)
		return;

	i_first = bit_ffs(job_resrcs_ptr->node_bitmap);
	i_last  = bit_fls(job_resrcs_ptr->node_bitmap);
	if (i_first == -1)
		return;

	if (step_ptr->mem_per_cpu && _is_mem_resv() &&
	    ((job_resrcs_ptr->memory_allocated == NULL) ||
	     (job_resrcs_ptr->memory_used == NULL))) {
		error("_step_dealloc_lps: lack memory allocation details "
		      "to enforce memory limits for job %u", job_ptr->job_id);
		step_ptr->mem_per_cpu = 0;
	}

	for (i_node = i_first; i_node <= i_last; i_node++) {
		if (!bit_test(job_resrcs_ptr->node_bitmap, i_node))
			continue;
		job_node_inx++;
		if (!bit_test(step_ptr->step_node_bitmap, i_node))
			continue;
		step_node_inx++;
		if (job_node_inx >= job_resrcs_ptr->nhosts)
			fatal("_step_dealloc_lps: node index bad");
		cpus_alloc = step_ptr->step_layout->tasks[step_node_inx] *
			     step_ptr->cpus_per_task;
		if (job_resrcs_ptr->cpus_used[job_node_inx] >= cpus_alloc)
			job_resrcs_ptr->cpus_used[job_node_inx] -= cpus_alloc;
		else {
			error("_step_dealloc_lps: cpu underflow for %u.%u",
				job_ptr->job_id, step_ptr->step_id);
			job_resrcs_ptr->cpus_used[job_node_inx] = 0;
		}
		if (step_ptr->mem_per_cpu && _is_mem_resv()) {
			uint32_t mem_use = step_ptr->mem_per_cpu * cpus_alloc;
			if (job_resrcs_ptr->memory_used[job_node_inx] >= mem_use) {
				job_resrcs_ptr->memory_used[job_node_inx] -=
						mem_use;
			} else {
				error("_step_dealloc_lps: "
				      "mem underflow for %u.%u",
				      job_ptr->job_id, step_ptr->step_id);
				job_resrcs_ptr->memory_used[job_node_inx] = 0;
			}
		}
		if (slurm_get_debug_flags() & DEBUG_FLAG_STEPS) {
			info("step dealloc of %s procs: %u of %u",
			     node_record_table_ptr[i_node].name,
			     job_resrcs_ptr->cpus_used[job_node_inx],
			     job_resrcs_ptr->cpus[job_node_inx]);
		}
		if (step_node_inx == (step_ptr->step_layout->node_cnt - 1))
			break;
	}

#ifndef HAVE_BG
	xassert(job_resrcs_ptr->core_bitmap);
	xassert(job_resrcs_ptr->core_bitmap_used);
	if (step_ptr->core_bitmap_job) {

		bit_not(step_ptr->core_bitmap_job);
		bit_and(job_resrcs_ptr->core_bitmap_used,
			step_ptr->core_bitmap_job);

		FREE_NULL_BITMAP(step_ptr->core_bitmap_job);
	}
#endif
}
