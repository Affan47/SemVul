_sort_job_by_time_limit(void *void1, void *void2)
{
	int diff;
	job_info_t *job1 = (job_info_t *) void1;
	job_info_t *job2 = (job_info_t *) void2;

	if (job1->time_limit > job2->time_limit)
		diff = 1;
	else if (job1->time_limit == job2->time_limit)
		diff = 0;
	else
		diff = -1;

	if (reverse_order)
		diff = -diff;
	return diff;
}
