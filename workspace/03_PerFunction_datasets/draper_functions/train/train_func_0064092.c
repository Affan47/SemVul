__db_stat_print_pp(dbp, flags)
	DB *dbp;
	u_int32_t flags;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	int handle_check, ret, t_ret;

	env = dbp->env;

	DB_ILLEGAL_BEFORE_OPEN(dbp, "DB->stat_print");


	if ((ret = __db_fchk(env,
	    "DB->stat_print", flags, DB_FAST_STAT | DB_STAT_ALL)) != 0)
		return (ret);

	ENV_ENTER(env, ip);


	handle_check = IS_ENV_REPLICATED(env);
	if (handle_check && (ret = __db_rep_enter(dbp, 1, 0, 0)) != 0) {
		handle_check = 0;
		goto err;
	}

	ret = __db_stat_print(dbp, ip, flags);


	if (handle_check && (t_ret = __env_db_rep_exit(env)) != 0 && ret == 0)
		ret = t_ret;

err:	ENV_LEAVE(env, ip);
	return (ret);
}
