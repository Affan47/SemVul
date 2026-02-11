job_submit_plugin_submit(struct job_descriptor *job_desc,
				    uint32_t submit_uid)
{
	int i, rc;

	rc = job_submit_plugin_init();
	slurm_mutex_lock(&g_context_lock);
	for (i=0; ((i < g_context_cnt) && (rc == SLURM_SUCCESS)); i++)
		rc = (*(ops[i].submit))(job_desc, submit_uid);
	slurm_mutex_unlock(&g_context_lock);
	return rc;
}
