_sort_by_partition(void *void1, void *void2)
{
	int diff;
	sinfo_data_t *sinfo1;
	sinfo_data_t *sinfo2;
	char *val1 = "", *val2 = "";

	_get_sinfo_from_void(&sinfo1, &sinfo2, void1, void2);

	if (part_order) {
		diff = (int)sinfo1->part_inx - (int)sinfo2->part_inx;
	} else {
		if (sinfo1->part_info && sinfo1->part_info->name)
			val1 = sinfo1->part_info->name;
		if (sinfo2->part_info && sinfo2->part_info->name)
			val2 = sinfo2->part_info->name;
		diff = strcmp(val1, val2);
	}

	if (reverse_order)
		diff = -diff;
	return diff;
}
