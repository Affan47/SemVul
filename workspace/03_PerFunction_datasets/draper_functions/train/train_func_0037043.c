__txn_dispatch_undo(env, txn, rdbt, key_lsn, txnlist)
	ENV *env;
	DB_TXN *txn;
	DBT *rdbt;
	DB_LSN *key_lsn;
	DB_TXNHEAD *txnlist;
{
	int ret;

	txnlist->td = txn->td;
	ret = __db_dispatch(env, &env->recover_dtab,
	    rdbt, key_lsn, DB_TXN_ABORT, txnlist);
	if (ret == DB_SURPRISE_KID) {
		F_SET(txn, TXN_CHILDCOMMIT);
		ret = 0;
	}
	if (ret == 0 && F_ISSET(txn, TXN_CHILDCOMMIT) && IS_ZERO_LSN(*key_lsn))
		ret = __db_txnlist_lsnget(env, txnlist, key_lsn, 0);

	return (ret);
}
