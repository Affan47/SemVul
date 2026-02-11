__db_exists(dbp, txn, key, flags)
	DB *dbp;
	DB_TXN *txn;
	DBT *key;
	u_int32_t flags;
{
	DBT data;
	int ret;


	STRIP_AUTO_COMMIT(flags);

	if ((ret = __db_fchk(dbp->env, "DB->exists", flags,
	    DB_READ_COMMITTED | DB_READ_UNCOMMITTED | DB_RMW)) != 0)
		return (ret);


	memset(&data, 0, sizeof(data));
	data.dlen = 0;
	data.flags = DB_DBT_PARTIAL | DB_DBT_USERMEM;

	return (dbp->get(dbp, txn, key, &data, flags));
}
