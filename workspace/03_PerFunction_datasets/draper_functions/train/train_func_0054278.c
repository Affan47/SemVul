select_p_select_nodeinfo_set_all(void)
{
	struct node_record *node_ptr = NULL;
	int i=0;
	static time_t last_set_all = 0;


	if (last_set_all && (last_node_update < last_set_all)) {
		debug2("Node select info for set all hasn't "
		       "changed since %ld",
		       (long)last_set_all);
		return SLURM_NO_CHANGE_IN_DATA;
	}
	last_set_all = last_node_update;

	for (i=0; i<node_record_count; i++) {
		select_nodeinfo_t *nodeinfo = NULL;

		node_ptr = node_record_table_ptr + i;


		select_g_select_nodeinfo_get(node_ptr->select_nodeinfo,
					     SELECT_NODEDATA_PTR, 0,
					     (void *)&nodeinfo);
		if(!nodeinfo) {
			error("no nodeinfo returned from structure");
			continue;
		}

		if ((node_ptr->node_state & NODE_STATE_COMPLETING) ||
		    (node_ptr->node_state == NODE_STATE_ALLOCATED)) {
			if (slurmctld_conf.fast_schedule)
				nodeinfo->alloc_cpus =
					node_ptr->config_ptr->cpus;
			else
				nodeinfo->alloc_cpus = node_ptr->cpus;
		} else
			nodeinfo->alloc_cpus = 0;
	}

	return SLURM_SUCCESS;
}
