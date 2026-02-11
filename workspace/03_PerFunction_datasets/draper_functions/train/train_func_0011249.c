destroy_config(void)
{
	int rc = SLURM_SUCCESS;

	if (cray_conf) {
		xfree(cray_conf->apbasil);
		xfree(cray_conf->apkill);
		xfree(cray_conf->alps_engine);
		xfree(cray_conf->sdb_db);
		xfree(cray_conf->sdb_host);
		xfree(cray_conf->sdb_pass);
		xfree(cray_conf->sdb_user);
		xfree(cray_conf);
	}

	return rc;
}
