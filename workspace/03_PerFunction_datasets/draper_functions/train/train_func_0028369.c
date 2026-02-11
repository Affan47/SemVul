__env_open(dbenv, db_home, flags, mode)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
	int mode;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	u_int32_t orig_flags;
	int register_recovery, ret, t_ret;

	ip = NULL;
	env = dbenv->env;
	register_recovery = 0;


	if ((ret = __env_config(dbenv, db_home, &flags, mode)) != 0)
		return (ret);


	orig_flags = dbenv->flags;


	if ((ret = __env_open_arg(dbenv, flags)) != 0)
		return (ret);


	if (LF_ISSET(DB_REGISTER)) {


		if (LF_ISSET(DB_FAILCHK_ISALIVE)) {
			(void)__env_set_thread_count(dbenv, 50);
			dbenv->is_alive = __envreg_isalive;
		}

		if ((ret =
		    __envreg_register(env, &register_recovery, flags)) != 0)
			goto err;
		if (register_recovery) {
			if (!LF_ISSET(DB_RECOVER)) {
				__db_errx(env, DB_STR("1567",
	    "The DB_RECOVER flag was not specified, and recovery is needed"));
				ret = DB_RUNRECOVERY;
				goto err;
			}
		} else
			LF_CLR(DB_RECOVER);
	}


retry:	if (LF_ISSET(DB_RECOVER | DB_RECOVER_FATAL))
#ifdef HAVE_REPLICATION
		if ((ret = __rep_reset_init(env)) != 0 ||
		    (ret = __env_remove_env(env)) != 0 ||
#else
		if ((ret = __env_remove_env(env)) != 0 ||
#endif
		    (ret = __env_refresh(dbenv, orig_flags, 0)) != 0)
			goto err;

	if ((ret = __env_attach_regions(dbenv, flags, orig_flags, 1)) != 0)
		goto err;


	if (LF_ISSET(DB_FAILCHK) && !register_recovery) {
		ENV_ENTER(env, ip);
		if ((ret = __env_failchk_int(dbenv)) != 0)
			goto err;
		ENV_LEAVE(env, ip);
	}

err:	if (ret != 0)
		(void)__env_refresh(dbenv, orig_flags, 0);

	if (register_recovery) {


		if (ret == 0 && (t_ret = __envreg_xunlock(env)) != 0)
			ret = t_ret;
		if (ret != 0)
			(void)__envreg_unregister(env, 1);
	}


	if (ret == DB_RUNRECOVERY && !register_recovery &&
	    !LF_ISSET(DB_RECOVER) && LF_ISSET(DB_REGISTER)) {
		LF_SET(DB_RECOVER);
		goto retry;
	}

	return (ret);
}
