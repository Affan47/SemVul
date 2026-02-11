p_mpi_hook_client_prelaunch(mpi_plugin_client_info_t *job, char ***env)
{
	int rc;

	debug("mpi/pmi2: client_prelaunch");

	rc = pmi2_setup_srun(job, env);
	if (rc != SLURM_SUCCESS) {
		return NULL;
	}

	if (pmi2_start_agent() < 0) {
		error("failed to start PMI2 agent thread");
		return NULL;
	}

	return (void *)0x12345678;
}
