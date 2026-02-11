__db_truncate(dbp, ip, txn, countp)
	DB *dbp;
	DB_THREAD_INFO *ip;
	DB_TXN *txn;
	u_int32_t *countp;
{
	DB *sdbp;
	DBC *dbc;
	ENV *env;
	u_int32_t scount;
	int ret, t_ret;

	env = dbp->env;
	dbc = NULL;
	ret = 0;


	if (dbp->type != DB_QUEUE && DB_IS_PRIMARY(dbp)) {
		if ((ret = __db_s_first(dbp, &sdbp)) != 0)
			return (ret);
		for (; sdbp != NULL && ret == 0; ret = __db_s_next(&sdbp, txn))
			if ((ret = __db_truncate(sdbp, ip, txn, &scount)) != 0)
				break;
		if (sdbp != NULL)
			(void)__db_s_done(sdbp, txn);
		if (ret != 0)
			return (ret);
	}

	DB_TEST_RECOVERY(dbp, DB_TEST_PREDESTROY, ret, NULL);


	if ((ret = __db_cursor(dbp, ip, txn, &dbc, 0)) != 0)
		return (ret);

	DEBUG_LWRITE(dbc, txn, "DB->truncate", NULL, NULL, 0);
#ifdef HAVE_PARTITION
	if (DB_IS_PARTITIONED(dbp))
		ret = __part_truncate(dbc, countp);
	else
#endif
	switch (dbp->type) {
	case DB_BTREE:
	case DB_RECNO:
		ret = __bam_truncate(dbc, countp);
		break;
	case DB_HASH:
		ret = __ham_truncate(dbc, countp);
		break;
	case DB_HEAP:
		ret = __heap_truncate(dbc, countp);
		break;
	case DB_QUEUE:
		ret = __qam_truncate(dbc, countp);
		break;
	case DB_UNKNOWN:
	default:
		ret = __db_unknown_type(env, "DB->truncate", dbp->type);
		break;
	}


	if (dbc != NULL && (t_ret = __dbc_close(dbc)) != 0 && ret == 0)
		ret = t_ret;


	if (ret == 0)
		ret = __blob_del_all(dbp, txn, 1);

	DB_TEST_RECOVERY(dbp, DB_TEST_POSTDESTROY, ret, NULL);

DB_TEST_RECOVERY_LABEL

	return (ret);
}
