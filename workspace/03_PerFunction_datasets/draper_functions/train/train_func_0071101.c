_build_part_bitmap(struct part_record *part_ptr)
{
	char *this_node_name;
	bitstr_t *old_bitmap;
	struct node_record *node_ptr;
	hostlist_t host_list;

	part_ptr->total_cpus = 0;
	part_ptr->total_nodes = 0;

	if (part_ptr->node_bitmap == NULL) {
		part_ptr->node_bitmap = bit_alloc(node_record_count);
		old_bitmap = NULL;
	} else {
		old_bitmap = bit_copy(part_ptr->node_bitmap);
		bit_nclear(part_ptr->node_bitmap, 0,
			   node_record_count - 1);
	}

	if (part_ptr->nodes == NULL) {
		_unlink_free_nodes(old_bitmap, part_ptr);
		FREE_NULL_BITMAP(old_bitmap);
		return 0;
	}

	if ((host_list = hostlist_create(part_ptr->nodes)) == NULL) {
		FREE_NULL_BITMAP(old_bitmap);
		error("hostlist_create error on %s, %m",
		      part_ptr->nodes);
		return ESLURM_INVALID_NODE_NAME;
	}

	while ((this_node_name = hostlist_shift(host_list))) {
		node_ptr = find_node_record(this_node_name);
		if (node_ptr == NULL) {
			error("_build_part_bitmap: invalid node name %s",
				this_node_name);
			free(this_node_name);
			FREE_NULL_BITMAP(old_bitmap);
			hostlist_destroy(host_list);
			return ESLURM_INVALID_NODE_NAME;
		}
		part_ptr->total_nodes++;
		if (slurmctld_conf.fast_schedule)
			part_ptr->total_cpus += node_ptr->config_ptr->cpus;
		else
			part_ptr->total_cpus += node_ptr->cpus;
		node_ptr->part_cnt++;
		xrealloc(node_ptr->part_pptr, (node_ptr->part_cnt *
			sizeof(struct part_record *)));
		node_ptr->part_pptr[node_ptr->part_cnt-1] = part_ptr;
		if (old_bitmap)
			bit_clear(old_bitmap,
				  (int) (node_ptr -
					 node_record_table_ptr));
		bit_set(part_ptr->node_bitmap,
			(int) (node_ptr - node_record_table_ptr));
		free(this_node_name);
	}
	hostlist_destroy(host_list);

	_unlink_free_nodes(old_bitmap, part_ptr);
	last_node_update = time(NULL);
	FREE_NULL_BITMAP(old_bitmap);
	return 0;
}
