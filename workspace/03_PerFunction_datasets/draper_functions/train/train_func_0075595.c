_sort_job_by_time_left(void *void1, void *void2)
{
	int diff;
	job_info_t *job1;
	job_info_t *job2;
	time_t time1, time2;

	_get_job_info_from_void(&job1, &job2, void1, void2);

	if ((job1->time_limit == INFINITE) || (job1->time_limit == NO_VAL))
		time1 = INFINITE;
	else
		time1 = job1->time_limit - job_time_used(job1);
	if ((job2->time_limit == INFINITE) || (job2->time_limit == NO_VAL))
		time2 = INFINITE;
	else
		time2 = job2->time_limit - job_time_used(job2);
	if (time1 > time2)
		diff = 1;
	else if (time1 == time2)
		diff = 0;
	else
		diff = -1;

	if (reverse_order)
		diff = -diff;
	return diff;
}
