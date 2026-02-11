_same_info(struct node_record *node1_ptr,
			   struct node_record *node2_ptr, time_t update_time)
{
	int i;

	if (node1_ptr == NULL)
		return 0;

	if (node1_ptr->node_state != node2_ptr->node_state)
		return 1;
	if (_str_cmp(node1_ptr->reason, node2_ptr->reason))
		return 2;
	if (update_time > last_node_update)
		return 0;

	if (slurmctld_conf.fast_schedule) {

		if (node1_ptr->config_ptr->cpus != node2_ptr->config_ptr->cpus)
			return 3;
	} else {

		if (node1_ptr->cpus != node2_ptr->cpus)
			return 4;
	}
	if (node1_ptr->part_cnt != node2_ptr->part_cnt)
		return 5;
	for (i=0; i<node1_ptr->part_cnt; i++) {
		if (node1_ptr->part_pptr[i] !=  node2_ptr->part_pptr[i])
			return 6;
	}
	if (_str_cmp(node1_ptr->arch, node2_ptr->arch))
		return 7;
	if (_str_cmp(node1_ptr->os, node2_ptr->os))
		return 8;
	if (update_time > 0)
		return 0;

	if (slurmctld_conf.fast_schedule) {

		if ((node1_ptr->config_ptr->real_memory !=
		     node2_ptr->config_ptr->real_memory) ||
		    (node1_ptr->config_ptr->tmp_disk !=
		     node2_ptr->config_ptr->tmp_disk) ||
		    (node1_ptr->config_ptr->cpus !=
		     node2_ptr->config_ptr->cpus))
			return 9;
	} else {
		if ((node1_ptr->real_memory != node2_ptr->real_memory) ||
		    (node1_ptr->tmp_disk    != node2_ptr->tmp_disk) ||
		    (node1_ptr->cpus        != node2_ptr->cpus))
			return 10;
	}
	if (_str_cmp(node1_ptr->config_ptr->feature,
		     node2_ptr->config_ptr->feature))
		return 11;

	if (_str_cmp(node1_ptr->config_ptr->gres,
		     node2_ptr->config_ptr->gres))
		return 12;

	return 0;
}
