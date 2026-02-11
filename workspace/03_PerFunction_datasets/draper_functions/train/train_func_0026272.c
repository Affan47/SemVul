slurm_get_jobacct_gather_type(void)
{
	char *jobacct_type = NULL;
	slurm_ctl_conf_t *conf;

	if (slurmdbd_conf) {
	} else {
		conf = slurm_conf_lock();
		jobacct_type = xstrdup(conf->job_acct_gather_type);
		slurm_conf_unlock();
	}
	return jobacct_type;
}
