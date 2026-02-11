CDB___ram_put(dbp, txn, key, data, flags)
	DB *dbp;
	DB_TXN *txn;
	DBT *key, *data;
	u_int32_t flags;
{
	DBC *dbc;
	db_recno_t recno;
	int ret, t_ret;

	PANIC_CHECK(dbp->dbenv);


	if ((ret = CDB___db_putchk(dbp,
	    key, data, flags, F_ISSET(dbp, DB_AM_RDONLY), 0)) != 0)
		return (ret);


	if ((ret = dbp->cursor(dbp, txn, &dbc, DB_WRITELOCK)) != 0)
		return (ret);

	DEBUG_LWRITE(dbc, txn, "ram_put", key, data, flags);


	if (flags == DB_APPEND) {
		if ((ret = CDB___ram_update(
		    dbc, DB_MAX_RECORDS, 0)) != 0 && ret == DB_NOTFOUND)
			ret = 0;
	} else
		ret = CDB___ram_getno(dbc, key, &recno, 1);


	if (ret == 0)
		ret = CDB___ram_add(dbc, &recno, data, flags, 0);


	if ((t_ret = dbc->c_close(dbc)) != 0 && ret == 0)
		ret = t_ret;


	if (ret == 0 && flags == DB_APPEND)
		*(db_recno_t *)key->data = recno;

	return (ret);
}
