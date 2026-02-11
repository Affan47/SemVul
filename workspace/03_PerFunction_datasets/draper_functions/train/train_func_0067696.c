get_current_worker_time() {
	struct batch_job_info *info;
	UINT64_T sum_running_worker_time = 0;
	UINT64_T key;

	itable_firstkey(job_table);
	while(itable_nextkey(job_table, &key, (void **)(&info))) {
		sum_running_worker_time += time(0) - info->submitted;
	}

	return sum_running_worker_time + total_worker_time;
}
