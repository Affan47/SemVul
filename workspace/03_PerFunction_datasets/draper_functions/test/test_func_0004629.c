pget(DbTxn *txnid, Dbt *key, Dbt *pkey, Dbt *value, u_int32_t flags)
{
	DB *db = unwrap(this);
	int ret;

	ret = db->pget(db, unwrap(txnid), key, pkey, value, flags);


	if (!DB_RETOK_DBGET(ret)) {
		if (ret == DB_BUFFER_SMALL && DB_OVERFLOWED_DBT(value))
			DB_ERROR_DBT(dbenv_, "Db::pget", value, error_policy());
		else
			DB_ERROR(dbenv_, "Db::pget", ret, error_policy());
	}

	return (ret);
}
