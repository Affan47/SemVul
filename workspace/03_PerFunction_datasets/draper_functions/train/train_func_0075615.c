__lock_downgrade(env, lock, new_mode, flags)
	ENV *env;
	DB_LOCK *lock;
	db_lockmode_t new_mode;
	u_int32_t flags;
{
	struct __db_lock *lockp;
	DB_LOCKER *sh_locker;
	DB_LOCKOBJ *obj;
	DB_LOCKREGION *region;
	DB_LOCKTAB *lt;
	int ret;

	ret = 0;


	if (F_ISSET(env->dbenv, DB_ENV_NOLOCKING))
		return (0);

	lt = env->lk_handle;
	region = lt->reginfo.primary;

	LOCK_SYSTEM_LOCK(lt, region);

	lockp = R_ADDR(&lt->reginfo, lock->off);
	if (lock->gen != lockp->gen) {
		__db_errx(env, LOCK_INVALID_ERR, "lock_downgrade");
		ret = EINVAL;
		goto out;
	}

	sh_locker = R_ADDR(&lt->reginfo, lockp->holder);

	if (IS_WRITELOCK(lockp->mode) && !IS_WRITELOCK(new_mode))
		sh_locker->nwrites--;

	lockp->mode = new_mode;
	lock->mode = new_mode;


	obj = SH_OFF_TO_PTR(lockp, lockp->obj, DB_LOCKOBJ);
	OBJECT_LOCK_NDX(lt, region, obj->indx);
	STAT(lt->obj_stat[obj->indx].st_ndowngrade++);
	ret = __lock_promote(lt, obj, NULL, flags);
	OBJECT_UNLOCK(lt, region, obj->indx);

out:	LOCK_SYSTEM_UNLOCK(lt, region);
	return (ret);
}
