__db_xa_prepare(xid, rmid, arg_flags)
	XID *xid;
	int rmid;
	long arg_flags;
{
	DB_ENV *dbenv;
	DB_TXN *txnp;
	ENV *env;
	TXN_DETAIL *td;
	int ret;
	u_long flags;

	flags = (u_long)arg_flags;
	ret = 0;

	if (LF_ISSET(TMASYNC))
		return (XAER_ASYNC);
	if (flags != TMNOFLAGS)
		return (XAER_INVAL);


	if (__db_rmid_to_env(rmid, &env) != 0)
		return (XAER_PROTO);
	dbenv = env->dbenv;


	PANIC_CHECK_RET(env, ret);
	if (ret == DB_RUNRECOVERY) {
		corrupted_env(env, rmid);
		if (__db_rmid_to_env(rmid, &env) != 0)
			return (XAER_PROTO);
		dbenv = env->dbenv;
	}

	if ((ret = __db_xid_to_txn(env, xid, &td)) != 0) {
		dbenv->err(dbenv, ret, DB_STR("4555",
		    "xa_prepare: failure mapping xid"));
		return (XAER_RMFAIL);
	}
	if (td == NULL) {
		dbenv->err(dbenv, EINVAL, DB_STR("4556",
		    "xa_prepare: xid not found"));
		return (XAER_NOTA);
	}

	if (td->xa_br_status == TXN_XA_DEADLOCKED)
		return (XA_RBDEADLOCK);
	if (td->xa_br_status == TXN_XA_ROLLEDBACK)
		return (XA_RBOTHER);

	if (td->xa_br_status != TXN_XA_ACTIVE &&
	    td->xa_br_status != TXN_XA_IDLE) {
		dbenv->err(dbenv, EINVAL, DB_STR("4557",
		    "xa_prepare: transaction neither active nor idle"));
		return (XAER_PROTO);
	}


	if ((ret = __xa_get_txn(env, xid, td, &txnp, TMJOIN, 0)) != 0)
		return (ret);

	if ((ret = txnp->prepare(txnp, (u_int8_t *)xid->data)) != 0) {
		dbenv->err(dbenv, ret, DB_STR("4558",
		    "xa_prepare: txnp->prepare failed"));
		td->xa_br_status = TXN_XA_IDLE;
		return (XAER_RMERR);
	}
	td->xa_br_status = TXN_XA_PREPARED;

	__xa_put_txn(env, txnp);
	return (XA_OK);
}
