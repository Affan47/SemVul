__rep_get_config(dbenv, which, onp)
	DB_ENV *dbenv;
	u_int32_t which;
	int *onp;
{
	DB_REP *db_rep;
	ENV *env;
	REP *rep;
	u_int32_t mapped;

	env = dbenv->env;

#undef	OK_FLAGS
#define	OK_FLAGS							\
    (DB_REP_CONF_AUTOINIT | DB_REP_CONF_AUTOROLLBACK |			\
    DB_REP_CONF_BULK | DB_REP_CONF_DELAYCLIENT | DB_REP_CONF_INMEM |	\
    DB_REP_CONF_LEASE | DB_REP_CONF_NOWAIT |				\
    DB_REPMGR_CONF_2SITE_STRICT | DB_REPMGR_CONF_ELECTIONS)

	if (FLD_ISSET(which, ~OK_FLAGS))
		return (__db_ferr(env, "DB_ENV->rep_get_config", 0));

	db_rep = env->rep_handle;
	ENV_NOT_CONFIGURED(
	    env, db_rep->region, "DB_ENV->rep_get_config", DB_INIT_REP);

	mapped = 0;
	__rep_config_map(env, &which, &mapped);
	if (REP_ON(env)) {
		rep = db_rep->region;
		if (FLD_ISSET(rep->config, mapped))
			*onp = 1;
		else
			*onp = 0;
	} else {
		if (FLD_ISSET(db_rep->config, mapped))
			*onp = 1;
		else
			*onp = 0;
	}
	return (0);
}
