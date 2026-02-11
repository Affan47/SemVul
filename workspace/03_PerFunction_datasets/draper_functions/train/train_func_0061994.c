init_dbsite(env, eid, host, port, sitep)
	ENV *env;
	int eid;
	const char *host;
	u_int port;
	DB_SITE **sitep;
{
	DB_SITE *dbsite;
	int ret;

	if ((ret = __os_calloc(env, 1, sizeof(DB_SITE), &dbsite)) != 0)
		return (ret);

	dbsite->env = env;
	dbsite->eid = eid;
	dbsite->host = host;
	dbsite->port = port;
	dbsite->flags = (REP_ON(env) ? 0 : DB_SITE_PREOPEN);

	dbsite->get_address = __repmgr_get_site_address;
	dbsite->get_config = __repmgr_get_config;
	dbsite->get_eid = __repmgr_get_eid;
	dbsite->set_config = __repmgr_site_config_pp;
	dbsite->remove = __repmgr_remove_site_pp;
	dbsite->close = __repmgr_site_close;

	*sitep = dbsite;
	return (0);
}
