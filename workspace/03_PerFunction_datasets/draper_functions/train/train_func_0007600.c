__lock_promote(lt, obj, state_changedp, flags)
	DB_LOCKTAB *lt;
	DB_LOCKOBJ *obj;
	int *state_changedp;
	u_int32_t flags;
{
	struct __db_lock *lp_w, *lp_h, *next_waiter;
	DB_LOCKREGION *region;
	int had_waiters, state_changed;

	region = lt->reginfo.primary;
	had_waiters = 0;


	for (lp_w = SH_TAILQ_FIRST(&obj->waiters, __db_lock),
	    state_changed = lp_w == NULL;
	    lp_w != NULL;
	    lp_w = next_waiter) {
		had_waiters = 1;
		next_waiter = SH_TAILQ_NEXT(lp_w, links, __db_lock);


		if (lp_w->status != DB_LSTAT_WAITING)
			continue;

		SH_TAILQ_FOREACH(lp_h, &obj->holders, links, __db_lock) {
			if (lp_h->holder != lp_w->holder &&
			    CONFLICTS(lt, region, lp_h->mode, lp_w->mode)) {
				if (!__lock_same_family(lt,
				     R_ADDR(&lt->reginfo, lp_h->holder),
				     R_ADDR(&lt->reginfo, lp_w->holder)))
					break;
			}
		}
		if (lp_h != NULL)
			break;


		SH_TAILQ_REMOVE(&obj->waiters, lp_w, links, __db_lock);
		lp_w->status = DB_LSTAT_PENDING;
		SH_TAILQ_INSERT_TAIL(&obj->holders, lp_w, links);


		MUTEX_UNLOCK(lt->env, lp_w->mtx_lock);
		state_changed = 1;
		if (LF_ISSET(DB_LOCK_ONEWAITER))
			break;
	}


	if (had_waiters && SH_TAILQ_FIRST(&obj->waiters, __db_lock) == NULL) {
		LOCK_DD(lt->env, region);


		obj->generation++;
		SH_TAILQ_REMOVE(&region->dd_objs, obj, dd_links, __db_lockobj);
		UNLOCK_DD(lt->env, region);
	}

	if (state_changedp != NULL)
		*state_changedp = state_changed;

	return (0);
}
