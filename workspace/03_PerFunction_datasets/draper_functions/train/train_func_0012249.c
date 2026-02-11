_add_reservation(uint32_t start_time, uint32_t end_reserve,
			     bitstr_t *res_bitmap,
			     node_space_map_t *node_space,
			     int *node_space_recs)
{
	bool placed = false;
	int i, j;


	start_time = (start_time / backfill_resolution) * backfill_resolution;
	end_reserve = (end_reserve / backfill_resolution) * backfill_resolution;

	for (j=0; ; ) {
		if (node_space[j].end_time > start_time) {

			i = *node_space_recs;
			node_space[i].begin_time = start_time;
			node_space[i].end_time = node_space[j].end_time;
			node_space[j].end_time = start_time;
			node_space[i].avail_bitmap =
				bit_copy(node_space[j].avail_bitmap);
			node_space[i].next = node_space[j].next;
			node_space[j].next = i;
			(*node_space_recs)++;
			placed = true;
		}
		if (node_space[j].end_time == start_time) {

			placed = true;
		}
		if (placed == true) {
			j = node_space[j].next;
			if (j && (end_reserve < node_space[j].end_time)) {

				i = *node_space_recs;
				node_space[i].begin_time = end_reserve;
				node_space[i].end_time = node_space[j].
							 end_time;
				node_space[j].end_time = end_reserve;
				node_space[i].avail_bitmap =
					bit_copy(node_space[j].avail_bitmap);
				node_space[i].next = node_space[j].next;
				node_space[j].next = i;
				(*node_space_recs)++;
			}
			break;
		}
		if ((j = node_space[j].next) == 0)
			break;
	}

	for (j=0; ; ) {
		if ((node_space[j].begin_time >= start_time) &&
		    (node_space[j].end_time <= end_reserve))
			bit_and(node_space[j].avail_bitmap, res_bitmap);
		if ((node_space[j].begin_time >= end_reserve) ||
		    ((j = node_space[j].next) == 0))
			break;
	}
}
