__lock_set_timeout(env, locker, timeout, op)
	ENV *env;
	DB_LOCKER *locker;
	db_timeout_t timeout;
	u_int32_t op;
{
	int ret;

	if (locker == NULL)
		return (0);
	LOCK_REGION_LOCK(env);
	ret = __lock_set_timeout_internal(env, locker, timeout, op);
	LOCK_REGION_UNLOCK(env);
	return (ret);
}
