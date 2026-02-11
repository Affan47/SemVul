__db_stat_pp(dbp, txn, spp, flags)
	DB *dbp;
	DB_TXN *txn;
	void *spp;
	u_int32_t flags;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	int handle_check, ret, t_ret;

	env = dbp->env;

	DB_ILLEGAL_BEFORE_OPEN(dbp, "DB->stat");

	if ((ret = __db_stat_arg(dbp, flags)) != 0)
		return (ret);

	ENV_ENTER(env, ip);


	handle_check = IS_ENV_REPLICATED(env);
	if (handle_check && (ret = __db_rep_enter(dbp, 1, 0,
	    IS_REAL_TXN(txn))) != 0) {
		handle_check = 0;
		goto err;
	}

	ret = __db_stat(dbp, ip, txn, spp, flags);


	if (handle_check && (t_ret = __env_db_rep_exit(env)) != 0 && ret == 0)
		ret = t_ret;

err:	ENV_LEAVE(env, ip);
	return (ret);
}
