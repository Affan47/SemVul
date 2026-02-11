_step_range_to_hostlist(struct step_record *step_ptr,
		uint32_t range_first, uint32_t range_last)
{
	int i, node_inx = -1;
	hostlist_t hl = hostlist_create("");

	for (i = 0; i < node_record_count; i++) {
		if (bit_test(step_ptr->step_node_bitmap, i) == 0)
			continue;
		node_inx++;
		if ((node_inx >= range_first)
		&&  (node_inx <= range_last)) {
			hostlist_push(hl,
				node_record_table_ptr[i].name);
		}
	}

	return hl;
}
