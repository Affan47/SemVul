CDB___db_xa_end(xid, rmid, flags)
	XID *xid;
	int rmid;
	long flags;
{
	DB_ENV *env;
	DB_TXN *txn;
	TXN_DETAIL *td;
	size_t off;

	if (flags != TMNOFLAGS && !LF_ISSET(TMSUSPEND | TMSUCCESS | TMFAIL))
		return (XAER_INVAL);

	if (CDB___db_rmid_to_env(rmid, &env) != 0)
		return (XAER_PROTO);

	if (CDB___db_xid_to_txn(env, xid, &off) != 0)
		return (XAER_NOTA);

	txn = env->xa_txn;
	if (off != txn->off)
		return (XAER_PROTO);

	td = (TXN_DETAIL *)R_ADDR(&((DB_TXNMGR *)env->tx_handle)->reginfo, off);
	if (td->xa_status == TXN_XA_DEADLOCKED)
		return (XA_RBDEADLOCK);

	if (td->status == TXN_ABORTED)
		return (XA_RBOTHER);

	if (td->xa_status != TXN_XA_STARTED)
		return (XAER_PROTO);


	td->last_lsn = txn->last_lsn;


	if (LF_ISSET(TMSUSPEND))
		td->xa_status = TXN_XA_SUSPENDED;
	else
		td->xa_status = TXN_XA_ENDED;

	txn->txnid = TXN_INVALID;
	return (XA_OK);
}
