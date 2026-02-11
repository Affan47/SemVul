__dd_abort(env, info, statusp)
	ENV *env;
	locker_info *info;
	int *statusp;
{
	struct __db_lock *lockp;
	DB_LOCKER *lockerp;
	DB_LOCKOBJ *sh_obj;
	DB_LOCKREGION *region;
	DB_LOCKTAB *lt;
	int ret;

	*statusp = 0;

	lt = env->lk_handle;
	region = lt->reginfo.primary;
	ret = 0;


	LOCK_SYSTEM_LOCK(lt, region);
	LOCK_LOCKERS(env, region);


	if ((ret = __lock_getlocker_int(lt,
	    info->last_locker_id, 0, NULL, &lockerp)) != 0)
		goto err;
	if (lockerp == NULL || F_ISSET(lockerp, DB_LOCKER_INABORT)) {
		*statusp = DB_ALREADY_ABORTED;
		goto err;
	}


	OBJECT_LOCK_NDX(lt, region, info->last_ndx);
	if ((lockp = SH_LIST_FIRST(&lockerp->heldby, __db_lock)) == NULL) {
		*statusp = DB_ALREADY_ABORTED;
		goto done;
	}
	if (R_OFFSET(&lt->reginfo, lockp) != info->last_lock ||
	    lockp->holder != R_OFFSET(&lt->reginfo, lockerp) ||
	    F_ISSET(lockerp, DB_LOCKER_INABORT) ||
	    lockp->obj != info->last_obj || lockp->status != DB_LSTAT_WAITING) {
		*statusp = DB_ALREADY_ABORTED;
		goto done;
	}

	sh_obj = SH_OFF_TO_PTR(lockp, lockp->obj, DB_LOCKOBJ);

	STAT_INC_VERB(env, lock, deadlock,
	    region->stat.st_ndeadlocks, lockerp->id, &sh_obj->lockobj);

	lockp->status = DB_LSTAT_ABORTED;
	SH_TAILQ_REMOVE(&sh_obj->waiters, lockp, links, __db_lock);


	if (SH_TAILQ_FIRST(&sh_obj->waiters, __db_lock) == NULL) {
		LOCK_DD(env, region);
		SH_TAILQ_REMOVE(&region->dd_objs,
		    sh_obj, dd_links, __db_lockobj);
		UNLOCK_DD(env, region);
	} else
		ret = __lock_promote(lt, sh_obj, NULL, 0);
	MUTEX_UNLOCK(env, lockp->mtx_lock);

done:	OBJECT_UNLOCK(lt, region, info->last_ndx);
err:	UNLOCK_LOCKERS(env, region);
	LOCK_SYSTEM_UNLOCK(lt, region);
	return (ret);
}
