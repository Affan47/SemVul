__lock_put(env, lock)
	ENV *env;
	DB_LOCK *lock;
{
	DB_LOCKTAB *lt;
	int ret, run_dd;

	if (IS_RECOVERING(env))
		return (0);

	lt = env->lk_handle;

	LOCK_SYSTEM_LOCK(lt, (DB_LOCKREGION *)lt->reginfo.primary);
	ret = __lock_put_nolock(env, lock, &run_dd, 0);
	LOCK_SYSTEM_UNLOCK(lt, (DB_LOCKREGION *)lt->reginfo.primary);


	if (ret == 0 && run_dd)
		(void)__lock_detect(env,
		    ((DB_LOCKREGION *)lt->reginfo.primary)->detect, NULL);
	return (ret);
}
