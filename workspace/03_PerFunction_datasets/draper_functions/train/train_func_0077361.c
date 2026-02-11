__db_xa_end(xid, rmid, arg_flags)
	XID *xid;
	int rmid;
	long arg_flags;
{
	DB_ENV *dbenv;
	DB_TXN *txn;
	ENV *env;
	TXN_DETAIL *td;
	int ret;
	u_long flags;

	flags = (u_long)arg_flags;
	if (flags != TMNOFLAGS && !LF_ISSET(TMSUSPEND | TMSUCCESS | TMFAIL))
		return (XAER_INVAL);

	if (__db_rmid_to_env(rmid, &env) != 0)
		return (XAER_PROTO);
	dbenv = env->dbenv;

	if ((ret = __db_xid_to_txn(env, xid, &td)) != 0) {
		dbenv->err(dbenv, ret, DB_STR("4551",
		    "xa_end: failure mapping xid"));
		return (XAER_RMFAIL);
	}
	if (td == NULL)
		return (XAER_NOTA);

	if ((ret = __xa_get_txn(env, xid, td, &txn, flags, 1)) != 0)
		return (ret);


	if (txn->cursors != 0) {
		dbenv->err(dbenv, EINVAL, DB_STR("4552",
		    "xa_end: cannot end with open cursors"));
		return (XAER_RMERR);
	}

	if (td != txn->td) {
		dbenv->err(dbenv, ret, DB_STR("4553",
		    "xa_end: txn_detail mismatch"));
		return (XAER_RMERR);
	}

	if (td->xa_br_status == TXN_XA_DEADLOCKED)
		return (XA_RBDEADLOCK);


	if (td->status == TXN_NEED_ABORT) {
		if (txn->abort(txn) != 0)
			return (XAER_RMERR);
		__xa_put_txn(env, txn);
		return (XA_RBOTHER);
	}

	if (td->xa_br_status == TXN_XA_IDLE) {
		dbenv->err(dbenv, EINVAL, DB_STR("4554",
		    "xa_end: ending transaction that is idle"));
		return (XAER_PROTO);
	}


	if (td->xa_ref == 1 && td->xa_br_status == TXN_XA_ACTIVE)
		td->xa_br_status = TXN_XA_IDLE;
	if (LF_ISSET(TMSUSPEND)) {
		txn->thread_info->dbth_xa_status = TXN_XA_THREAD_SUSPENDED;
		txn->xa_thr_status = TXN_XA_THREAD_SUSPENDED;
	} else {
		__xa_put_txn(env, txn);
	}
	return (XA_OK);
}
