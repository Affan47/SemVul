_make_assoc_limit_vals(slurmdb_association_rec_t *assoc, char **vals)
{
	char *tmp = NULL;

	if(!assoc)
		return SLURM_ERROR;

	if((int)assoc->shares_raw >= 0) {
		xstrfmtcat(*vals, ", shares=%u", assoc->shares_raw);
	} else if (((int)assoc->shares_raw == INFINITE)) {
		xstrcat(*vals, ", shares=1");
		assoc->shares_raw = 1;
	}

	concat_limit_64("grp_cpu_mins", assoc->grp_cpu_mins, &tmp, vals);
	concat_limit_64("grp_cpu_run_mins", assoc->grp_cpu_run_mins,
			&tmp, vals);
	concat_limit_32("grp_cpus", assoc->grp_cpus, &tmp, vals);
	concat_limit_32("grp_jobs", assoc->grp_jobs, &tmp, vals);
	concat_limit_32("grp_mem", assoc->grp_mem, &tmp, vals);
	concat_limit_32("grp_nodes", assoc->grp_nodes, &tmp, vals);
	concat_limit_32("grp_submit_jobs", assoc->grp_submit_jobs, &tmp, vals);
	concat_limit_32("grp_wall", assoc->grp_wall, &tmp, vals);
	concat_limit_64("max_cpu_mins_pj",
			assoc->max_cpu_mins_pj, &tmp, vals);
	concat_limit_64("max_cpu_run_mins",
			assoc->max_cpu_run_mins, &tmp, vals);
	concat_limit_32("max_cpus_pj", assoc->max_cpus_pj, &tmp, vals);
	concat_limit_32("max_jobs", assoc->max_jobs, &tmp, vals);
	concat_limit_32("max_nodes_pj", assoc->max_nodes_pj, &tmp, vals);
	concat_limit_32("max_submit_jobs", assoc->max_submit_jobs, &tmp, vals);
	concat_limit_32("max_wall_pj",
			assoc->max_wall_pj, &tmp, vals);
	xfree(tmp);
	return SLURM_SUCCESS;
}
