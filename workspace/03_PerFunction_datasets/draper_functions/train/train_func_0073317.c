__db_join_close_pp(dbc)
	DBC *dbc;
{
	DB *dbp;
	DB_THREAD_INFO *ip;
	ENV *env;
	int handle_check, ret, t_ret;

	dbp = dbc->dbp;
	env = dbp->env;

	ENV_ENTER(env, ip);

	handle_check = IS_ENV_REPLICATED(env);
	if (handle_check &&
	    (ret = __db_rep_enter(dbp, 1, 0, IS_REAL_TXN(dbc->txn))) != 0) {
		handle_check = 0;
		goto err;
	}

	ret = __db_join_close(dbc);

	if (handle_check && (t_ret = __env_db_rep_exit(env)) != 0 && ret == 0)
		ret = t_ret;

err:	ENV_LEAVE(env, ip);
	return (ret);
}
