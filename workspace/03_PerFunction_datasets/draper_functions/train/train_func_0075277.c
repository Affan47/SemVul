__add_recycle_lsn_range(lvinfo, lsn, min, max)
	DB_LOG_VRFY_INFO *lvinfo;
	const DB_LSN *lsn;
	u_int32_t min, max;
{
	DBC *csr;
	int ret, tret;
	u_int32_t i;
	DBT key2, data2;
	struct __add_recycle_params param;

	csr = NULL;
	ret = tret = 0;
	memset(&key2, 0, sizeof(DBT));
	memset(&data2, 0, sizeof(DBT));
	memset(&param, 0, sizeof(param));

	if ((ret = __os_malloc(lvinfo->dbenv->env, sizeof(VRFY_TXN_INFO *) *
	    (param.ti2ul = 1024), &(param.ti2u))) != 0)
		goto err;
	param.ti2ui = 0;
	param.recycle_lsn = *lsn;
	param.min = min;
	param.max = max;


	if ((ret = __iterate_txninfo(lvinfo, min, max, __lv_add_recycle_handler,
	    &param)) != 0)
		goto err;


	BDBOP(__db_cursor(lvinfo->txninfo, lvinfo->ip, NULL, &csr, DBC_BULK));

	for (i = 0; i < param.ti2ui; i++) {
		ret = __lv_pack_txn_vrfy_info(param.ti2u[i], &key2, &data2);
		DB_ASSERT(lvinfo->dbenv->env, ret == 0);
		BDBOP(__dbc_put(csr, &key2, &data2, DB_KEYLAST));


		if ((ret = __free_txninfo(param.ti2u[i])) != 0)
			goto err;
	}

err:
	if (csr != NULL && (tret = __dbc_close(csr)) != 0 && ret == 0)
		ret = tret;
	__os_free(lvinfo->dbenv->env, param.ti2u);
	if (ret != 0)
		__db_err(lvinfo->dbenv->env, ret,
		    "__add_recycle_lsn_range");

	return (ret);
}
