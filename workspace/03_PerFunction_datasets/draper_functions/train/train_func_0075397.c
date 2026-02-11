_slurm_cgroup_destroy(void)
{
	if (slurm_freezer_init)
		xcgroup_lock(&slurm_freezer_cg);

	if (jobstep_cgroup_path[0] != '\0') {
		if ( xcgroup_delete(&step_freezer_cg) != XCGROUP_SUCCESS ) {
			if (slurm_freezer_init)
				xcgroup_unlock(&slurm_freezer_cg);
			return SLURM_ERROR;
		}
		xcgroup_destroy(&step_freezer_cg);
	}

	if (job_cgroup_path[0] != '\0') {
		xcgroup_delete(&job_freezer_cg);
		xcgroup_destroy(&job_freezer_cg);
	}

	if (user_cgroup_path[0] != '\0') {
		xcgroup_delete(&user_freezer_cg);
		xcgroup_destroy(&user_freezer_cg);
	}

	if (slurm_freezer_init) {
		xcgroup_unlock(&slurm_freezer_cg);
		xcgroup_destroy(&slurm_freezer_cg);
	}

	xcgroup_ns_destroy(&freezer_ns);

	return SLURM_SUCCESS;
}
