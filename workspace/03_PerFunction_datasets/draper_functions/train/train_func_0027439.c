__lock_wakeup(env, obj)
	ENV *env;
	const DBT *obj;
{
	DB_LOCKOBJ *sh_obj;
	DB_LOCKREGION *region;
	DB_LOCKTAB *lt;
	u_int32_t ndx;
	int ret;


	if (F_ISSET(env->dbenv, DB_ENV_NOLOCKING))
		return (0);

	lt = env->lk_handle;
	region = lt->reginfo.primary;

	OBJECT_LOCK(lt, region, obj, ndx);
	if ((ret = __lock_getobj(lt, obj, ndx, 0, &sh_obj)) == 0 &&
	    sh_obj != NULL)
		ret = __lock_promote(lt, sh_obj, NULL, DB_LOCK_ONEWAITER);

	OBJECT_UNLOCK(lt, region, ndx);
	return (ret);
}
