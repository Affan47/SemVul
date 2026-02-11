_update_sview_part_sub(sview_part_sub_t *sview_part_sub,
				   node_info_t *node_ptr,
				   int node_scaling)
{
	int cpus_per_node = 1;
	int idle_cpus = node_ptr->cpus;
	uint16_t err_cpus = 0, alloc_cpus = 0;

	if (node_scaling)
		cpus_per_node = node_ptr->cpus / node_scaling;

	xassert(sview_part_sub);
	xassert(sview_part_sub->node_ptr_list);
	xassert(sview_part_sub->hl);

	if (sview_part_sub->node_cnt == 0) {
		sview_part_sub->node_state = node_ptr->node_state;
		sview_part_sub->features   = xstrdup(node_ptr->features);
		sview_part_sub->reason     = xstrdup(node_ptr->reason);
	} else if (hostlist_find(sview_part_sub->hl, node_ptr->name) != -1) {


		g_print("already been here\n");
		return;
	}

	if ((sview_part_sub->node_state & NODE_STATE_BASE)
	    == NODE_STATE_MIXED) {
		slurm_get_select_nodeinfo(node_ptr->select_nodeinfo,
					  SELECT_NODEDATA_SUBCNT,
					  NODE_STATE_ALLOCATED,
					  &alloc_cpus);
		if (cluster_flags & CLUSTER_FLAG_BG) {
			if (!alloc_cpus
			    && (IS_NODE_ALLOCATED(node_ptr)
				|| IS_NODE_COMPLETING(node_ptr)))
				alloc_cpus = node_ptr->cpus;
			else
				alloc_cpus *= cpus_per_node;
		}
		idle_cpus -= alloc_cpus;

		slurm_get_select_nodeinfo(node_ptr->select_nodeinfo,
					  SELECT_NODEDATA_SUBCNT,
					  NODE_STATE_ERROR,
					  &err_cpus);
		if (cluster_flags & CLUSTER_FLAG_BG)
			err_cpus *= cpus_per_node;

		idle_cpus -= err_cpus;
	} else if (sview_part_sub->node_state == NODE_STATE_ALLOCATED) {
		alloc_cpus = idle_cpus;
		idle_cpus = 0;
	} else if (sview_part_sub->node_state != NODE_STATE_IDLE) {
		err_cpus = idle_cpus;
		idle_cpus = 0;
	}

	sview_part_sub->cpu_alloc_cnt += alloc_cpus;
	sview_part_sub->cpu_error_cnt += err_cpus;
	sview_part_sub->cpu_idle_cnt += idle_cpus;
	sview_part_sub->disk_total += node_ptr->tmp_disk;
	sview_part_sub->mem_total  += node_ptr->real_memory;
	sview_part_sub->node_cnt   += node_scaling;
	list_append(sview_part_sub->node_ptr_list, node_ptr);
	hostlist_push(sview_part_sub->hl, node_ptr->name);
}
