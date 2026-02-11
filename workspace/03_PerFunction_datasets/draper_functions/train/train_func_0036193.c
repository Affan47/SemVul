CDB___db_xa_rollback(xid, rmid, flags)
	XID *xid;
	int rmid;
	long flags;
{
	DB_ENV *env;
	TXN_DETAIL *td;
	size_t off;

	if (LF_ISSET(TMASYNC))
		return (XAER_ASYNC);
	if (flags != TMNOFLAGS)
		return (XAER_INVAL);

	if (CDB___db_rmid_to_env(rmid, &env) != 0)
		return (XAER_PROTO);

	if (CDB___db_xid_to_txn(env, xid, &off) != 0)
		return (XAER_NOTA);

	td = (TXN_DETAIL *)R_ADDR(&((DB_TXNMGR *)env->tx_handle)->reginfo, off);
	if (td->xa_status == TXN_XA_DEADLOCKED)
		return (XA_RBDEADLOCK);

	if (td->xa_status == TXN_XA_ABORTED)
		return (XA_RBOTHER);

	if (td->xa_status != TXN_XA_ENDED && td->xa_status != TXN_XA_SUSPENDED
	    && td->xa_status != TXN_XA_PREPARED)
		return (XAER_PROTO);


	CDB___xa_txn_init(env, td, off);
	if (CDB_txn_abort(env->xa_txn) != 0)
		return (XAER_RMERR);


	CDB___xa_txn_end(env);
	return (XA_OK);
}
