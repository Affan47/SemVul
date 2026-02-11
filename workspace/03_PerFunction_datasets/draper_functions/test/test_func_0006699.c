__db_create_internal(dbpp, env, flags)
	DB **dbpp;
	ENV *env;
	u_int32_t flags;
{
	DB *dbp;
	DB_ENV *dbenv;
	DB_REP *db_rep;
	int ret;

	*dbpp = NULL;


	if (env == NULL) {
		if ((ret = db_env_create(&dbenv, 0)) != 0)
			return (ret);
		env = dbenv->env;
		F_SET(env, ENV_DBLOCAL);
	} else
		dbenv = env->dbenv;


	if ((ret = __os_calloc(env, 1, sizeof(*dbp), &dbp)) != 0)
		goto err;

	dbp->dbenv = env->dbenv;
	dbp->env = env;
	if ((ret = __db_init(dbp, flags)) != 0)
		goto err;

	MUTEX_LOCK(env, env->mtx_dblist);
	++env->db_ref;
	MUTEX_UNLOCK(env, env->mtx_dblist);


	dbp->timestamp = REP_ON(env) ?
	    ((REGENV *)env->reginfo->primary)->rep_timestamp : 0;


	db_rep = env->rep_handle;
	dbp->fid_gen = REP_ON(env) ? ((REP *)db_rep->region)->gen : 0;


	if ((ret = __memp_fcreate(env, &dbp->mpf)) != 0)
		goto err;

	dbp->type = DB_UNKNOWN;

	*dbpp = dbp;
	return (0);

err:	if (dbp != NULL) {
		if (dbp->mpf != NULL)
			(void)__memp_fclose(dbp->mpf, 0);
		__os_free(env, dbp);
	}

	if (dbp != NULL && F_ISSET(env, ENV_DBLOCAL))
		(void)__env_close(dbp->dbenv, 0);

	return (ret);
}
