__db_cursor(dbp, ip, txn, dbcp, flags)
	DB *dbp;
	DB_THREAD_INFO *ip;
	DB_TXN *txn;
	DBC **dbcp;
	u_int32_t flags;
{
	DBC *dbc;
	ENV *env;
	db_lockmode_t mode;
	int ret;

	env = dbp->env;

	if (MULTIVERSION(dbp) && txn == NULL && (LF_ISSET(DB_TXN_SNAPSHOT) ||
	    F_ISSET(env->dbenv, DB_ENV_TXN_SNAPSHOT))) {
		if ((ret =
		    __txn_begin(env, ip, NULL, &txn, DB_TXN_SNAPSHOT)) != 0)
			return (ret);
		F_SET(txn, TXN_PRIVATE);
	}

	PERFMON5(env, db, cursor, dbp->fname,
	    dbp->dname, txn == NULL ? 0 : txn->txnid, flags, &dbp->fileid[0]);

	if ((ret = __db_cursor_int(dbp, ip, txn, dbp->type, PGNO_INVALID,
	    LF_ISSET(DB_CURSOR_BULK | DB_CURSOR_TRANSIENT | DB_RECOVER),
	    NULL, &dbc)) != 0)
		return (ret);


	if (CDB_LOCKING(env)) {
		mode = (LF_ISSET(DB_WRITELOCK)) ? DB_LOCK_WRITE :
		    ((LF_ISSET(DB_WRITECURSOR) || txn != NULL) ?
		    DB_LOCK_IWRITE : DB_LOCK_READ);
		if ((ret = __lock_get(env, dbc->locker, 0,
		    &dbc->lock_dbt, mode, &dbc->mylock)) != 0)
			goto err;
		if (LF_ISSET(DB_WRITECURSOR))
			F_SET(dbc, DBC_WRITECURSOR);
		if (LF_ISSET(DB_WRITELOCK))
			F_SET(dbc, DBC_WRITER);
	}

	if (LF_ISSET(DB_READ_UNCOMMITTED) ||
	    (txn != NULL && F_ISSET(txn, TXN_READ_UNCOMMITTED)))
		F_SET(dbc, DBC_READ_UNCOMMITTED);

	if (LF_ISSET(DB_READ_COMMITTED) ||
	    (txn != NULL && F_ISSET(txn, TXN_READ_COMMITTED)))
		F_SET(dbc, DBC_READ_COMMITTED);

	*dbcp = dbc;
	return (0);

err:	(void)__dbc_close(dbc);
	return (ret);
}
