__lock_set_lk_max_objects(dbenv, lk_max)
	DB_ENV *dbenv;
	u_int32_t lk_max;
{
	ENV *env;

	env = dbenv->env;

	ENV_ILLEGAL_AFTER_OPEN(env, "DB_ENV->set_lk_max_objects");

	dbenv->lk_max_objects = lk_max;
	return (0);
}
