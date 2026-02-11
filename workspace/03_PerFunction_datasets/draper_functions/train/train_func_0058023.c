CDB___bam_c_rget(dbc, data, flags)
	DBC *dbc;
	DBT *data;
	u_int32_t flags;
{
	BTREE_CURSOR *cp;
	DB *dbp;
	DBT dbt;
	db_recno_t recno;
	int exact, ret;

	COMPQUIET(flags, 0);
	dbp = dbc->dbp;
	cp = dbc->internal;


	if ((ret = CDB_memp_fget(dbp->mpf, &cp->pgno, 0, &cp->page)) != 0)
		return (ret);


	memset(&dbt, 0, sizeof(DBT));
	dbt.flags = DB_DBT_MALLOC | DB_DBT_INTERNAL;
	if ((ret = CDB___db_ret(dbp, cp->page, cp->indx, &dbt, NULL, NULL)) != 0)
		goto err;

	exact = 1;
	if ((ret = CDB___bam_search(dbc, &dbt,
	    F_ISSET(dbc, DBC_RMW) ? S_FIND_WR : S_FIND,
	    1, &recno, &exact)) != 0)
		goto err;

	ret = CDB___db_retcopy(dbp, data,
	    &recno, sizeof(recno), &dbc->rdata.data, &dbc->rdata.ulen);


	CDB___bam_stkrel(dbc, 0);

err:	(void)CDB_memp_fput(dbp->mpf, cp->page, 0);
	CDB___os_free(dbt.data, dbt.size);
	return (ret);
}
