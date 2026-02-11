__env_close_pp(dbenv, flags)
	DB_ENV *dbenv;
	u_int32_t flags;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	int ret, t_ret;
	u_int32_t close_flags, flags_orig;

	env = dbenv->env;
	ret = 0;
	close_flags = flags_orig = 0;


	if (flags != 0 && flags != DB_FORCESYNC &&
	    (t_ret = __db_ferr(env, "DB_ENV->close", 0)) != 0 && ret == 0)
		ret = t_ret;

#define	DBENV_FORCESYNC		0x00000001
#define	DBENV_CLOSE_REPCHECK	0x00000010
	if (flags == DB_FORCESYNC)
		close_flags |= DBENV_FORCESYNC;


	if (PANIC_ISSET(env)) {

		if (dbenv->registry != NULL) {


			flags_orig = F_ISSET(dbenv, DB_ENV_NOPANIC);
			F_SET(dbenv, DB_ENV_NOPANIC);
			ENV_ENTER(env, ip);
			(void)__envreg_unregister(env, 0);
			ENV_LEAVE(env, ip);
			dbenv->registry = NULL;
			if (!flags_orig)
				F_CLR(dbenv, DB_ENV_NOPANIC);
		}


		(void)__repmgr_close(env);


		flags_orig = F_ISSET(dbenv, DB_ENV_NOPANIC);
		F_SET(dbenv, DB_ENV_NOPANIC);
		ENV_ENTER(env, ip);
		(void)__file_handle_cleanup(env);
		ENV_ENTER(env, ip);
		if (!flags_orig)
			F_CLR(dbenv, DB_ENV_NOPANIC);

		PANIC_CHECK(env);
	}

	ENV_ENTER(env, ip);

#ifdef HAVE_REPLICATION_THREADS


	if ((t_ret = __repmgr_close(env)) != 0 && ret == 0)
		ret = t_ret;
#endif
	if (IS_ENV_REPLICATED(env)) {
		if ((t_ret = __env_rep_enter(env, 0)) != 0 && ret == 0)
			ret = t_ret;
		if (ret == 0)
			close_flags |= DBENV_CLOSE_REPCHECK;
	}

	if ((t_ret = __env_close(dbenv, close_flags)) != 0 && ret == 0)
		ret = t_ret;


	return (ret);
}
