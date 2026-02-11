_sort_by_job_size(void *void1, void *void2)
{
	int diff;
	sinfo_data_t *sinfo1;
	sinfo_data_t *sinfo2;
	uint32_t val1 = 0, val2 = 0;

	_get_sinfo_from_void(&sinfo1, &sinfo2, void1, void2);

	if (sinfo1->part_info) {
		val1 = sinfo1->part_info->max_nodes;
		if (val1 != INFINITE)
			val1 += sinfo1->part_info->min_nodes;
	}
	if (sinfo2->part_info) {
		val2 = sinfo2->part_info->max_nodes;
		if (val2 != INFINITE)
			val2 += sinfo2->part_info->min_nodes;
	}
	diff = val1 - val2;

	if (reverse_order)
		diff = -diff;
	return diff;
}
