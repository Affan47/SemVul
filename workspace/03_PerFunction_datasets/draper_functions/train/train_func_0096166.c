__lock_inherit_locks(lt, sh_locker, flags)
	DB_LOCKTAB *lt;
	DB_LOCKER *sh_locker;
	u_int32_t flags;
{
	DB_LOCKER *sh_parent;
	DB_LOCKOBJ *obj;
	DB_LOCKREGION *region;
	ENV *env;
	int ret;
	struct __db_lock *hlp, *lp;
	roff_t poff;

	env = lt->env;
	region = lt->reginfo.primary;


	if (sh_locker == NULL) {
		__db_errx(env, LOCKER_INVALID_ERR);
		return (EINVAL);
	}


	if (sh_locker->parent_locker == INVALID_ROFF) {
		__db_errx(env, DB_STR("2039", "Not a child transaction"));
		return (EINVAL);
	}
	sh_parent = R_ADDR(&lt->reginfo, sh_locker->parent_locker);


	poff = R_OFFSET(&lt->reginfo, sh_parent);
	for (lp = SH_LIST_FIRST(&sh_locker->heldby, __db_lock);
	    lp != NULL;
	    lp = SH_LIST_FIRST(&sh_locker->heldby, __db_lock)) {
		SH_LIST_REMOVE(lp, locker_links, __db_lock);


		obj = SH_OFF_TO_PTR(lp, lp->obj, DB_LOCKOBJ);
		OBJECT_LOCK_NDX(lt, region, obj->indx);
		SH_TAILQ_FOREACH(hlp, &obj->holders, links, __db_lock)
			if (hlp->holder == poff && lp->mode == hlp->mode)
				break;

		if (hlp != NULL) {

			hlp->refcount += lp->refcount;


			DB_ASSERT(env, lp->status == DB_LSTAT_HELD);
			SH_TAILQ_REMOVE(&obj->holders, lp, links, __db_lock);
			(void)__lock_freelock(lt, lp, sh_locker, DB_LOCK_FREE);
		} else {

			SH_LIST_INSERT_HEAD(&sh_parent->heldby,
			    lp, locker_links, __db_lock);
			lp->holder = poff;
			sh_parent->nlocks++;
			if (IS_WRITELOCK(lp->mode))
				sh_parent->nwrites++;
		}


		ret = __lock_promote(lt, obj, NULL, flags);
		OBJECT_UNLOCK(lt, region, obj->indx);
		if (ret != 0)
			return (ret);
	}

	return (0);
}
