_setup_stepd_job_info(const slurmd_job_t *job, char ***env)
{
	char *p;
	int i;

	memset(&job_info, 0, sizeof(job_info));

	job_info.jobid  = job->jobid;
	job_info.stepid = job->stepid;
	job_info.nnodes = job->nnodes;
	job_info.nodeid = job->nodeid;
	job_info.ntasks = job->ntasks;
	job_info.ltasks = job->node_tasks;
	job_info.gtids = xmalloc(job->node_tasks * sizeof(uint32_t));
	for (i = 0; i < job->node_tasks; i ++) {
		job_info.gtids[i] = job->task[i]->gtid;
	}

	p = getenvp(*env, PMI2_PMI_DEBUGGED_ENV);
	if (p) {
		job_info.pmi_debugged = atoi(p);
	} else {
		job_info.pmi_debugged = 0;
	}
	p = getenvp(*env, PMI2_SPAWN_SEQ_ENV);
	if (p) {
		job_info.spawn_seq = atoi(p);
		unsetenvp(*env, PMI2_SPAWN_SEQ_ENV);
		p = getenvp(*env, PMI2_SPAWNER_JOBID_ENV);
		job_info.spawner_jobid = xstrdup(p);
		unsetenvp(*env, PMI2_SPAWNER_JOBID_ENV);
	} else {
		job_info.spawn_seq = 0;
		job_info.spawner_jobid = NULL;
	}
	p = getenvp(*env, PMI2_PMI_JOBID_ENV);
	if (p) {
		job_info.pmi_jobid = xstrdup(p);
		unsetenvp(*env, PMI2_PMI_JOBID_ENV);
	} else {
		xstrfmtcat(job_info.pmi_jobid, "%u.%u", job->jobid,
			   job->stepid);
	}
	p = getenvp(*env, PMI2_STEP_NODES_ENV);
	if (!p) {
		error("mpi/pmi2: unable to find nodes in job environment");
		return SLURM_ERROR;
	} else {
		job_info.step_nodelist = xstrdup(p);
		unsetenvp(*env, PMI2_STEP_NODES_ENV);
	}


	p = getenvp(*env, PMI2_PROC_MAPPING_ENV);
	if (!p) {
		error("PMI2_PROC_MAPPING_ENV not found");
		return SLURM_ERROR;
	} else {
		job_info.proc_mapping = xstrdup(p);
		unsetenvp(*env, PMI2_PROC_MAPPING_ENV);
	}

	job_info.job_env = env_array_copy((const char **)*env);

	job_info.srun_job = NULL;
	job_info.srun_opt = NULL;

	return SLURM_SUCCESS;
}
