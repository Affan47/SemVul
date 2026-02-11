dlmconvert_remote(struct dlm_ctxt *dlm,
				  struct dlm_lock_resource *res,
				  struct dlm_lock *lock, int flags, int type)
{
	enum dlm_status status;

	mlog(0, "type=%d, convert_type=%d, busy=%d\n", lock->ml.type,
	     lock->ml.convert_type, res->state & DLM_LOCK_RES_IN_PROGRESS);

	spin_lock(&res->spinlock);
	if (res->state & DLM_LOCK_RES_RECOVERING) {
		mlog(0, "bailing out early since res is RECOVERING "
		     "on secondary queue\n");

		status = DLM_RECOVERING;
		goto bail;
	}

	__dlm_wait_on_lockres(res);

	if (lock->ml.convert_type != LKM_IVMODE) {
		__dlm_print_one_lock_resource(res);
		mlog(ML_ERROR, "converting a remote lock that is already "
		     "converting! (cookie=%u:%llu, conv=%d)\n",
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ml.convert_type);
		status = DLM_DENIED;
		goto bail;
	}

	if (lock->ml.type == type && lock->ml.convert_type == LKM_IVMODE) {
		mlog(0, "last convert request returned DLM_RECOVERING, but "
		     "owner has already queued and sent ast to me. res %.*s, "
		     "(cookie=%u:%llu, type=%d, conv=%d)\n",
		     res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ml.type, lock->ml.convert_type);
		status = DLM_NORMAL;
		goto bail;
	}

	res->state |= DLM_LOCK_RES_IN_PROGRESS;


	list_move_tail(&lock->list, &res->converting);
	lock->convert_pending = 1;
	lock->ml.convert_type = type;

	if (flags & LKM_VALBLK) {
		if (lock->ml.type == LKM_EXMODE) {
			flags |= LKM_PUT_LVB;
			lock->lksb->flags |= DLM_LKSB_PUT_LVB;
		} else {
			if (lock->ml.convert_type == LKM_NLMODE)
				flags &= ~LKM_VALBLK;
			else {
				flags |= LKM_GET_LVB;
				lock->lksb->flags |= DLM_LKSB_GET_LVB;
			}
		}
	}
	spin_unlock(&res->spinlock);


	status = dlm_send_remote_convert_request(dlm, res, lock, flags, type);

	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;


	if (status != DLM_NORMAL) {
		if (status != DLM_NOTQUEUED)
			dlm_error(status);
		dlm_revert_pending_convert(res, lock);
	} else if (!lock->convert_pending) {
		mlog(0, "%s: res %.*s, owner died and lock has been moved back "
				"to granted list, retry convert.\n",
				dlm->name, res->lockname.len, res->lockname.name);
		status = DLM_RECOVERING;
	}

	lock->convert_pending = 0;
bail:
	spin_unlock(&res->spinlock);


	wake_up(&res->wq);

	return status;
}
