__memp_get_mp_pagesize(dbenv, mp_pagesizep)
	DB_ENV *dbenv;
	u_int32_t *mp_pagesizep;
{
	DB_MPOOL *dbmp;
	ENV *env;
	MPOOL *mp;

	env = dbenv->env;

	ENV_NOT_CONFIGURED(env,
	    env->mp_handle, "DB_ENV->get_mp_max_pagesize", DB_INIT_MPOOL);

	if (MPOOL_ON(env)) {
		dbmp = env->mp_handle;
		mp = dbmp->reginfo[0].primary;
		*mp_pagesizep = mp->pagesize;
	} else {
		*mp_pagesizep = dbenv->mp_pagesize;
	}
	return (0);
}
