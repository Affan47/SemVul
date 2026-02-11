create_dir_config(apr_pool_t *p, char *d)
{
	char *dname = d;
	ruid_dir_config_t *dconf = apr_pcalloc (p, sizeof(*dconf));

	if (dname == NULL) {

		dconf->ruid_mode=RUID_MODE_CONF;
	} else {

		dconf->ruid_mode=RUID_MODE_UNDEFINED;
	}
	dconf->ruid_uid=UNSET;
	dconf->ruid_gid=UNSET;
	dconf->groupsnr=UNSET;

	return dconf;
}
