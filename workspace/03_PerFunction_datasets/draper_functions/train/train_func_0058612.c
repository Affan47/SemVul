_can_job_run_on_node(struct job_record *job_ptr, bitstr_t *core_map,
			      const uint32_t node_i,
			      struct node_use_record *node_usage,
			      uint16_t cr_type,
			      bool test_only)
{
	uint16_t cpus;
	uint32_t avail_mem, req_mem, gres_cpus;
	int core_start_bit, core_end_bit;
	struct node_record *node_ptr = node_record_table_ptr + node_i;
	List gres_list;

	if (!test_only && IS_NODE_COMPLETING(node_ptr)) {

		cpus = 0;
		return cpus;
	}

	cpus = _allocate_cores(job_ptr, core_map, node_i);

	core_start_bit = cr_get_coremap_offset(node_i);
	core_end_bit   = cr_get_coremap_offset(node_i + 1) - 1;
	node_ptr = select_node_record[node_i].node_ptr;

	if ((cr_type & CR_MEMORY) && cpus) {
		req_mem   = job_ptr->details->pn_min_memory & ~MEM_PER_CPU;
		avail_mem = select_node_record[node_i].real_memory;
		if (!test_only)
			avail_mem -= node_usage[node_i].alloc_memory;
		if (req_mem > avail_mem)
			cpus = 0;
	}

	if (node_usage[node_i].gres_list)
		gres_list = node_usage[node_i].gres_list;
	else
		gres_list = node_ptr->gres_list;
	gres_cpus = gres_plugin_job_test(job_ptr->gres_list,
					 gres_list, test_only,
					 core_map, core_start_bit,
					 core_end_bit, job_ptr->job_id,
					 node_ptr->name);
	if ((gres_cpus < job_ptr->details->ntasks_per_node) ||
	    ((job_ptr->details->cpus_per_task > 1) &&
	     (gres_cpus < job_ptr->details->cpus_per_task)))
		gres_cpus = 0;
	if (gres_cpus < cpus)
		cpus = gres_cpus;

	if (cpus == 0)
		bit_nclear(core_map, core_start_bit, core_end_bit);

	if (select_debug_flags & DEBUG_FLAG_CPU_BIND) {
		info("select/serial: _can_job_run_on_node: %u cpus on %s(%d), "
		     "mem %u/%u",
		     cpus, select_node_record[node_i].node_ptr->name,
		     node_usage[node_i].node_state,
		     node_usage[node_i].alloc_memory,
		     select_node_record[node_i].real_memory);
	}

	return cpus;
}
