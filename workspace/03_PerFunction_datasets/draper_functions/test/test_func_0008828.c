finish_gmdb_update(env, ip, key_dbt, prev_status, status, flags, logrec)
	ENV *env;
	DB_THREAD_INFO *ip;
	DBT *key_dbt;
	u_int32_t prev_status, status, flags;
	__repmgr_member_args *logrec;
{
	DB_REP *db_rep;
	DB_LSN lsn;
	DB_TXN *txn;
	DBT data_dbt;
	u_int8_t data_buf[__REPMGR_MEMBERSHIP_DATA_SIZE];
	int ret, t_ret;

	db_rep = env->rep_handle;

	db_rep->active_gmdb_update = gmdb_secondary;
	if ((ret = __txn_begin(env, ip, NULL, &txn, DB_IGNORE_LEASE)) != 0)
		return (ret);

	if (status == 0)
		ret = __db_del(db_rep->gmdb, ip, txn, key_dbt, 0);
	else {
		marshal_site_data(env, status, flags, data_buf, &data_dbt);
		ret = __db_put(db_rep->gmdb, ip, txn, key_dbt, &data_dbt, 0);
	}
	if (ret != 0)
		goto err;

	if ((ret = incr_gm_version(env, ip, txn)) != 0)
		goto err;

	ZERO_LSN(lsn);
	if ((ret = __repmgr_member_log(env,
	    txn, &lsn, 0, db_rep->membership_version,
	    prev_status, status, &logrec->host, logrec->port)) != 0)
		goto err;

err:
	if ((t_ret = __db_txn_auto_resolve(env, txn, 0, ret)) != 0 && ret == 0)
		ret = t_ret;
	return (ret);
}
