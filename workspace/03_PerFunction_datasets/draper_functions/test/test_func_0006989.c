valid_spank_job_env(char **spank_job_env,
			        uint32_t spank_job_env_size, uid_t uid)
{
	int i;
	char *entry;

	for (i=0; i<spank_job_env_size; i++) {
		if (!strncmp(spank_job_env[i], "SPANK_", 6))
			continue;
		entry = spank_job_env[i];
		spank_job_env[i] = xstrdup_printf ("SPANK_%s", entry);
		xfree (entry);
	}
	return true;
}
