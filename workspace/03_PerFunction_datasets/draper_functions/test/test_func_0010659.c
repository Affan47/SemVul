__memp_remove_region(dbmp)
	DB_MPOOL *dbmp;
{
	DB_MPOOL_HASH *hp;
	ENV *env;
	MPOOL *mp, *c_mp;
	REGINFO *infop;
	int ret;
	u_int i;

	env = dbmp->env;
	mp = dbmp->reginfo[0].primary;
	ret = 0;

	if (mp->nreg == 1) {
		__db_errx(env, DB_STR("3019",
		    "cannot remove the last cache"));
		return (EINVAL);
	}

	for (i = 0; i < mp->htab_buckets; i++)
		if ((ret = __memp_remove_bucket(dbmp)) != 0)
			return (ret);


	infop = &dbmp->reginfo[mp->nreg - 1];
	c_mp = infop->primary;
	hp = R_ADDR(infop, c_mp->htab);


	if (F_ISSET(env, ENV_PRIVATE)) {
		if ((ret = __memp_region_bhfree(infop)) != 0)
			return (ret);
		if (MUTEX_ON(env)) {
			DB_ASSERT(env,
			    env->dbenv->mp_mtxcount == mp->htab_mutexes);
			for (i = 0; i < mp->htab_mutexes; i++)
				if ((ret = __mutex_free(env,
				    &hp[i].mtx_hash)) != 0)
					return (ret);
		}
		__env_alloc_free(infop, hp);
	} else if (MUTEX_ON(env)) {
		DB_ASSERT(env, env->dbenv->mp_mtxcount == mp->htab_mutexes);
		for (i = 0; i < mp->htab_mutexes; i++)
			if ((ret = __mutex_refresh(env, hp[i].mtx_hash)) != 0)
				return (ret);
	}

	ret = __env_region_detach(env, infop, 1);
	if  (ret == 0)
		mp->nreg--;

	return (ret);
}
