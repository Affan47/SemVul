_sview_job_sort_aval_dec(void *s1, void *s2)
{
	sview_job_info_t* rec_a = *(sview_job_info_t **)s1;
	sview_job_info_t* rec_b = *(sview_job_info_t **)s2;
	int size_a;
	int size_b;

	size_a = rec_a->node_cnt;
	size_b = rec_b->node_cnt;

	if (size_a < size_b)
		return -1;
	else if (size_a > size_b)
		return 1;

	if (rec_a->nodes && rec_b->nodes) {
		size_a = strcmp(rec_a->nodes, rec_b->nodes);
		if (size_a < 0)
			return -1;
		else if (size_a > 0)
			return 1;
	}
	return 0;
}
