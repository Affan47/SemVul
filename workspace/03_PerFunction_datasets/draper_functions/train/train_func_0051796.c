build_job_resources_cpus_array(job_resources_t *job_resrcs_ptr)
{
	int cpu_count = 0, cpu_inx, i, j;

	if (job_resrcs_ptr->nhosts == 0)
		return cpu_count;
	if (job_resrcs_ptr->cpu_array_cnt == 0) {
		error("build_job_resources_cpus_array: cpu_array_cnt==0");
		return -1;
	}
	if (job_resrcs_ptr->cpu_array_value == NULL) {
		error("build_job_resources_cpus_array: cpu_array_value==NULL");
		return -1;
	}
	if (job_resrcs_ptr->cpu_array_reps == NULL) {
		error("build_job_resources_cpus_array: cpu_array_reps==NULL");
		return -1;
	}


	xfree(job_resrcs_ptr->cpus);
	job_resrcs_ptr->cpus =
		xmalloc(job_resrcs_ptr->nhosts * sizeof(uint16_t));

	cpu_inx = 0;
	for (i=0; i<job_resrcs_ptr->cpu_array_cnt; i++) {
		for (j=0; j<job_resrcs_ptr->cpu_array_reps[i]; j++) {
			if (cpu_inx >= job_resrcs_ptr->nhosts) {
				error("build_job_resources_cpus_array: "
				      "cpu_array is too long");
				return -1;
			}
			cpu_count += job_resrcs_ptr->cpus[i];
			job_resrcs_ptr->cpus[cpu_inx++] =
				job_resrcs_ptr->cpus[i];
		}
	}
	if (cpu_inx < job_resrcs_ptr->nhosts) {
		error("build_job_resources_cpus_array: "
		      "cpu_array is incomplete");
		return -1;
	}
	return cpu_count;
}
