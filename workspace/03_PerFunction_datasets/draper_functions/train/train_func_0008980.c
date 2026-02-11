_run_job_script(const char *name, const char *path,
		uint32_t jobid, int timeout, char **env)
{
	int status, rc;


	status = run_spank_job_script(name, env);
	if ((rc = run_script(name, path, jobid, timeout, env)))
		status = rc;
	return (status);
}
