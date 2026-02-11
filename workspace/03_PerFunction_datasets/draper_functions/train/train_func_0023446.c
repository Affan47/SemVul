_clear_used_assoc_info(slurmdb_association_rec_t *assoc)
{
	if (!assoc || !assoc->usage)
		return SLURM_ERROR;

	assoc->usage->grp_used_cpus = 0;
	assoc->usage->grp_used_mem = 0;
	assoc->usage->grp_used_nodes = 0;
	assoc->usage->grp_used_cpu_run_secs = 0;

	assoc->usage->used_jobs  = 0;
	assoc->usage->used_submit_jobs = 0;


	return SLURM_SUCCESS;
}
