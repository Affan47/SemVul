__db_key_range_pp(dbp, txn, key, kr, flags)
	DB *dbp;
	DB_TXN *txn;
	DBT *key;
	DB_KEY_RANGE *kr;
	u_int32_t flags;
{
	DBC *dbc;
	DB_THREAD_INFO *ip;
	ENV *env;
	int handle_check, ret, t_ret;

	env = dbp->env;

	DB_ILLEGAL_BEFORE_OPEN(dbp, "DB->key_range");


	if (flags != 0)
		return (__db_ferr(env, "DB->key_range", 0));

	ENV_ENTER(env, ip);
	XA_CHECK_TXN(ip, txn);


	handle_check = IS_ENV_REPLICATED(env);
	if (handle_check &&
	     (ret = __db_rep_enter(dbp, 1, 0, IS_REAL_TXN(txn))) != 0) {
		handle_check = 0;
		goto err;
	}


	if ((ret = __db_check_txn(dbp, txn, DB_LOCK_INVALIDID, 1)) != 0)
		goto err;


	switch (dbp->type) {
	case DB_BTREE:
		if ((ret = __dbt_usercopy(env, key)) != 0)
			goto err;


		if ((ret = __db_cursor(dbp, ip, txn, &dbc, 0)) != 0) {
			__dbt_userfree(env, key, NULL, NULL);
			break;
		}

		DEBUG_LWRITE(dbc, NULL, "bam_key_range", NULL, NULL, 0);
#ifdef HAVE_PARTITION
		if (DB_IS_PARTITIONED(dbp))
			ret = __part_key_range(dbc, key, kr, flags);
		else
#endif
			ret = __bam_key_range(dbc, key, kr, flags);

		if ((t_ret = __dbc_close(dbc)) != 0 && ret == 0)
			ret = t_ret;
		__dbt_userfree(env, key, NULL, NULL);
		break;
	case DB_HASH:
	case DB_QUEUE:
	case DB_RECNO:
		ret = __dbh_am_chk(dbp, DB_OK_BTREE);
		break;
	case DB_UNKNOWN:
	default:
		ret = __db_unknown_type(env, "DB->key_range", dbp->type);
		break;
	}

err:
	if (handle_check && (t_ret = __env_db_rep_exit(env)) != 0 && ret == 0)
		ret = t_ret;

	ENV_LEAVE(env, ip);
	return (ret);
}
