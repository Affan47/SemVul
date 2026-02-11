task_cgroup_devices_fini(slurm_cgroup_conf_t *slurm_cgroup_conf)
{

	if ( user_cgroup_path[0] != '\0' )
		xcgroup_destroy(&user_devices_cg);
	if ( job_cgroup_path[0] != '\0' )
		xcgroup_destroy(&job_devices_cg);
	if ( jobstep_cgroup_path[0] != '\0' )
		xcgroup_destroy(&step_devices_cg);

	user_cgroup_path[0] = '\0';
	job_cgroup_path[0] = '\0';
	jobstep_cgroup_path[0] = '\0';

	cgroup_allowed_devices_file[0] = '\0';

	xcgroup_ns_destroy(&devices_ns);

	xcpuinfo_fini();
	return SLURM_SUCCESS;
}
