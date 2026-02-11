CDB___txn_regop_recover(dbenv, dbtp, lsnp, redo, info)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	int redo;
	void *info;
{
	__txn_regop_args *argp;
	int ret;

#ifdef DEBUG_RECOVER
	(void)CDB___txn_regop_print(dbenv, dbtp, lsnp, redo, info);
#endif
	COMPQUIET(redo, 0);
	COMPQUIET(dbenv, NULL);

	if ((ret = CDB___txn_regop_read(dbtp->data, &argp)) != 0)
		return (ret);

	if (argp->opcode != TXN_COMMIT)
		ret = EINVAL;
	else
		if (CDB___db_txnlist_find(info, argp->txnid->txnid) == DB_NOTFOUND)
			ret = CDB___db_txnlist_add(info, argp->txnid->txnid);

	if (ret == 0)
		*lsnp = argp->prev_lsn;
	CDB___os_free(argp, 0);

	return (ret);
}
