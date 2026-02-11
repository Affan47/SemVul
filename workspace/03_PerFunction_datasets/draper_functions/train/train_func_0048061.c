__env_remove(dbenv, db_home, flags)
	DB_ENV *dbenv;
	const char *db_home;
	u_int32_t flags;
{
	ENV *env;
	int ret, t_ret;

	env = dbenv->env;

#undef	OKFLAGS
#define	OKFLAGS								\
	(DB_FORCE | DB_USE_ENVIRON | DB_USE_ENVIRON_ROOT)


	if ((ret = __db_fchk(env, "DB_ENV->remove", flags, OKFLAGS)) != 0)
		return (ret);

	ENV_ILLEGAL_AFTER_OPEN(env, "DB_ENV->remove");

	if ((ret = __env_config(dbenv, db_home, &flags, 0)) != 0)
		return (ret);


	if ((ret = __env_turn_off(env, flags)) == 0 || LF_ISSET(DB_FORCE))
		ret = __env_remove_env(env);

	if ((t_ret = __env_close(dbenv, 0)) != 0 && ret == 0)
		ret = t_ret;

	return (ret);
}
