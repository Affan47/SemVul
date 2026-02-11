_delay_rpc(int pmi_rank, int pmi_size)
{
	struct timeval tv1, tv2;
	uint32_t cur_time;
	uint32_t tot_time;
	uint32_t offset_time;
	uint32_t target_time;
	uint32_t delta_time, error_time;
	int retries = 0;

	_set_pmi_time();

again:	if (gettimeofday(&tv1, NULL)) {
		usleep(pmi_rank * pmi_time);
		return;
	}

	cur_time = ((tv1.tv_sec % 1000) * 1000000) + tv1.tv_usec;
	tot_time = pmi_size * pmi_time;
	offset_time = cur_time % tot_time;
	target_time = pmi_rank * pmi_time;
	if (target_time < offset_time)
		delta_time = target_time - offset_time + tot_time;
	else
		delta_time = target_time - offset_time;
	if (usleep(delta_time)) {
		if (errno == EINVAL)
			usleep(900000);

		goto again;
	}


	if (gettimeofday(&tv2, NULL))
		return;
	tot_time = (tv2.tv_sec - tv1.tv_sec) * 1000000;
	tot_time += tv2.tv_usec;
	tot_time -= tv1.tv_usec;
	if (tot_time >= delta_time)
		error_time = tot_time - delta_time;
	else
		error_time = delta_time - tot_time;
	if (error_time > (15*pmi_time)) {
#if 0
		info("delta=%u tot=%u err=%u",
			delta_time, tot_time, error_time);
#endif
		if ((++retries) <= 2)
			goto again;
	}
}
