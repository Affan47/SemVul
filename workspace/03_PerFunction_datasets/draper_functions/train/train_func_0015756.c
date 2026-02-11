allocate_test(void)
{
	int rc;
	job_desc_msg_t *j = job_desc_msg_create_from_opts();
	if (!j)
		return SLURM_ERROR;

	rc = slurm_job_will_run(j);
	job_desc_msg_destroy(j);
	return rc;
}
