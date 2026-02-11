select_p_select_nodeinfo_set_all(void)
{
	struct part_res_record *p_ptr;
	struct node_record *node_ptr = NULL;
	int i=0, n=0, start, end;
	uint16_t tmp, tmp_16 = 0, tmp_part;
	static time_t last_set_all = 0;
	uint32_t node_threads, node_cpus;


	if (last_set_all && (last_node_update < last_set_all)) {
		debug2("Node select info for set all hasn't "
		       "changed since %ld",
		       (long)last_set_all);
		return SLURM_NO_CHANGE_IN_DATA;
	}
	last_set_all = last_node_update;

	for (n = 0, node_ptr = node_record_table_ptr;
	     n < select_node_cnt; n++, node_ptr++) {
		select_nodeinfo_t *nodeinfo = NULL;


		select_g_select_nodeinfo_get(node_ptr->select_nodeinfo,
					     SELECT_NODEDATA_PTR, 0,
					     (void *)&nodeinfo);
		if (!nodeinfo) {
			error("no nodeinfo returned from structure");
			continue;
		}

		if (slurmctld_conf.fast_schedule) {
			node_cpus    = node_ptr->config_ptr->cpus;
			node_threads = node_ptr->config_ptr->threads;
		} else {
			node_cpus    = node_ptr->cpus;
			node_threads = node_ptr->threads;
		}

		start = cr_get_coremap_offset(n);
		end = cr_get_coremap_offset(n+1);
		tmp_16 = 0;
		for (p_ptr = select_part_record; p_ptr; p_ptr = p_ptr->next) {
			if (!p_ptr->row)
				continue;
			tmp_part = 0;
			for (i = 0; i < p_ptr->num_rows; i++) {
				if (!p_ptr->row[i].row_bitmap)
					continue;
				tmp = bit_set_count_range(p_ptr->row[i].row_bitmap,
							  start, end);

				tmp_part = MAX(tmp, tmp_part);
			}
			tmp_16 += tmp_part;
		}


		if ((end - start) < node_cpus)
			tmp_16 *= node_threads;

		nodeinfo->alloc_cpus = tmp_16;
		if (select_node_record) {
			nodeinfo->alloc_memory =
				select_node_usage[n].alloc_memory;
		} else {
			nodeinfo->alloc_memory = 0;
		}
	}

	return SLURM_SUCCESS;
}
