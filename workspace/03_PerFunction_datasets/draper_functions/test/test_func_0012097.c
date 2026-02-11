CDB___bam_c_first(dbc)
	DBC *dbc;
{
	BTREE_CURSOR *cp;
	DB *dbp;
	db_pgno_t pgno;
	int ret;

	dbp = dbc->dbp;
	cp = dbc->internal;
	ret = 0;


	for (pgno = ((BTREE *)dbp->bt_internal)->bt_root;;) {
		ACQUIRE(dbc, pgno, DB_LOCK_READ, ret);
		if (ret != 0)
			return (ret);


		if (ISLEAF(cp->page))
			break;

		pgno = GET_BINTERNAL(cp->page, 0)->pgno;
	}


	if (F_ISSET(dbc, DBC_RMW)) {
		ACQUIRE_WRITE_LOCK(dbc, ret);
		if (ret != 0)
			return (ret);
	}

	cp->pgno = cp->page->pgno;
	cp->indx = 0;
	cp->dpgno = PGNO_INVALID;


	if (NUM_ENT(cp->page) > 0)
		if ((ret = CDB___bam_dup(dbc, cp->indx, 0)) != 0)
			return (ret);
	if (NUM_ENT(cp->page) == 0 || IS_CUR_DELETED(cp))
		if ((ret = CDB___bam_c_next(dbc, 0)) != 0)
			return (ret);

	return (0);
}
