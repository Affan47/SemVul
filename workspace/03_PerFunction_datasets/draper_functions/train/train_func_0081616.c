_cpus_to_use(int *avail_cpus, int rem_cpus, int rem_nodes,
			 struct job_details *details_ptr, uint16_t *cpu_cnt)
{
	int resv_cpus;

	if (details_ptr->shared == 0)
		return;

	resv_cpus = MAX((rem_nodes - 1), 0);
	resv_cpus *= details_ptr->pn_min_cpus;
	rem_cpus -= resv_cpus;

	if (*avail_cpus > rem_cpus) {
		*avail_cpus = MAX(rem_cpus, (int)details_ptr->pn_min_cpus);
		*cpu_cnt = *avail_cpus;
	}
}
