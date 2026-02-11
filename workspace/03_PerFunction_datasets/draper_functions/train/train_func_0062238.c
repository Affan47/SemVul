txn_begin(DbTxn *pid, DbTxn **tid, u_int32_t flags)
{
	DB_ENV *dbenv = unwrap(this);
	DB_TXN *txn;
	int ret;

	ret = dbenv->txn_begin(dbenv, unwrap(pid), &txn, flags);
	if (DB_RETOK_STD(ret))
		*tid = new DbTxn(txn, pid);
	else
		DB_ERROR(this, "DbEnv::txn_begin", ret, error_policy());

	return (ret);
}
