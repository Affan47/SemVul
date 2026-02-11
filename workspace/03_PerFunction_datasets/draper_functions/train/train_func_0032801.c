__env_get_home(dbenv, homep)
	DB_ENV *dbenv;
	const char **homep;
{
	ENV *env;

	env = dbenv->env;

	ENV_ILLEGAL_BEFORE_OPEN(env, "DB_ENV->get_home");
	*homep = env->db_home;

	return (0);
}
