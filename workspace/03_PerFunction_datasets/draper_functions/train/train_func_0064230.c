init (void)
{


	if (_run_in_daemon()) {
		jag_common_init(0);


		if (read_slurm_cgroup_conf(&slurm_cgroup_conf))
			return SLURM_ERROR;


		if (xcpuinfo_init() != XCPUINFO_SUCCESS) {
			free_slurm_cgroup_conf(&slurm_cgroup_conf);
			return SLURM_ERROR;
		}


		if (jobacct_gather_cgroup_cpuacct_init(&slurm_cgroup_conf) !=
		    SLURM_SUCCESS) {
			xcpuinfo_fini();
			free_slurm_cgroup_conf(&slurm_cgroup_conf);
			return SLURM_ERROR;
		}


		if (jobacct_gather_cgroup_memory_init(&slurm_cgroup_conf) !=
		    SLURM_SUCCESS) {
			xcpuinfo_fini();
			free_slurm_cgroup_conf(&slurm_cgroup_conf);
			return SLURM_ERROR;
		}


	}

	verbose("%s loaded", plugin_name);
	return SLURM_SUCCESS;
}
