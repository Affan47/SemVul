__db_get(dbp, ip, txn, key, data, flags)
	DB *dbp;
	DB_THREAD_INFO *ip;
	DB_TXN *txn;
	DBT *key, *data;
	u_int32_t flags;
{
	DBC *dbc;
	u_int32_t mode;
	int ret, t_ret;


	mode = DB_CURSOR_TRANSIENT;
	if (LF_ISSET(DB_READ_UNCOMMITTED)) {
		mode |= DB_READ_UNCOMMITTED;
		LF_CLR(DB_READ_UNCOMMITTED);
	} else if (LF_ISSET(DB_READ_COMMITTED)) {
		mode |= DB_READ_COMMITTED;
		LF_CLR(DB_READ_COMMITTED);
	} else if ((flags & DB_OPFLAGS_MASK) == DB_CONSUME ||
	    (flags & DB_OPFLAGS_MASK) == DB_CONSUME_WAIT)
		mode |= DB_WRITELOCK;

	if ((ret = __db_cursor(dbp, ip, txn, &dbc, mode)) != 0)
		return (ret);

	DEBUG_LREAD(dbc, txn, "DB->get", key, NULL, flags);


	F_SET(dbc, DBC_FROM_DB_GET);


	SET_RET_MEM(dbc, dbp);

	if (LF_ISSET(~(DB_RMW | DB_MULTIPLE)) == 0)
		LF_SET(DB_SET);

#ifdef HAVE_PARTITION
	if (F_ISSET(dbc, DBC_PARTITIONED))
		ret = __partc_get(dbc, key, data, flags);
	else
#endif
		ret = __dbc_get(dbc, key, data, flags);

	if (dbc != NULL && (t_ret = __dbc_close(dbc)) != 0 && ret == 0)
		ret = t_ret;

	return (ret);
}
