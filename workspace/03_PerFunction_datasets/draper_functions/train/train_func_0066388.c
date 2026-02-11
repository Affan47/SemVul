_build_bitmaps_pre_select(void)
{
	struct part_record   *part_ptr;
	struct node_record   *node_ptr;
	ListIterator part_iterator;
	int i;


	part_iterator = list_iterator_create(part_list);
	if (part_iterator == NULL)
		fatal ("memory allocation failure");

	while ((part_ptr = (struct part_record *) list_next(part_iterator))) {
		FREE_NULL_BITMAP(part_ptr->node_bitmap);

		if ((part_ptr->nodes == NULL) || (part_ptr->nodes[0] == '\0')) {

			part_ptr->node_bitmap = bit_alloc(node_record_count);
			continue;
		}

		if (node_name2bitmap(part_ptr->nodes, false,
				     &part_ptr->node_bitmap)) {
			fatal("Invalid node names in partition %s",
			      part_ptr->name);
		}

		for (i=0; i<node_record_count; i++) {
			if (bit_test(part_ptr->node_bitmap, i) == 0)
				continue;
			node_ptr = &node_record_table_ptr[i];
			part_ptr->total_nodes++;
			if (slurmctld_conf.fast_schedule)
				part_ptr->total_cpus +=
					node_ptr->config_ptr->cpus;
			else
				part_ptr->total_cpus += node_ptr->cpus;
			node_ptr->part_cnt++;
			xrealloc(node_ptr->part_pptr, (node_ptr->part_cnt *
				sizeof(struct part_record *)));
			node_ptr->part_pptr[node_ptr->part_cnt-1] = part_ptr;
		}
	}
	list_iterator_destroy(part_iterator);
	return;
}
