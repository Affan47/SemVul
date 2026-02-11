CDB___db_ditem(dbc, pagep, indx, nbytes)
	DBC *dbc;
	PAGE *pagep;
	u_int32_t indx, nbytes;
{
	DB *dbp;
	DBT ldbt;
	db_indx_t cnt, offset;
	int ret;
	u_int8_t *from;

	dbp = dbc->dbp;
	if (DB_LOGGING(dbc)) {
		ldbt.data = P_ENTRY(pagep, indx);
		ldbt.size = nbytes;
		if ((ret = CDB___db_addrem_log(dbp->dbenv, dbc->txn,
		    &LSN(pagep), 0, DB_REM_DUP, dbp->log_fileid, PGNO(pagep),
		    (u_int32_t)indx, nbytes, &ldbt, NULL, &LSN(pagep))) != 0)
			return (ret);
	}


	if (NUM_ENT(pagep) == 1) {
		NUM_ENT(pagep) = 0;
		HOFFSET(pagep) = dbp->pgsize;
		return (0);
	}


	from = (u_int8_t *)pagep + HOFFSET(pagep);
	memmove(from + nbytes, from, pagep->inp[indx] - HOFFSET(pagep));
	HOFFSET(pagep) += nbytes;


	offset = pagep->inp[indx];
	for (cnt = 0; cnt < NUM_ENT(pagep); ++cnt)
		if (pagep->inp[cnt] < offset)
			pagep->inp[cnt] += nbytes;


	--NUM_ENT(pagep);
	if (indx != NUM_ENT(pagep))
		memmove(&pagep->inp[indx], &pagep->inp[indx + 1],
		    sizeof(db_indx_t) * (NUM_ENT(pagep) - indx));

	return (0);
}
