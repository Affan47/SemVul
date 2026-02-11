__ham_truncate_overflow(dbc, indx, c_data, pgs_done)
	DBC *dbc;
	u_int32_t indx;
	DB_COMPACT *c_data;
	int *pgs_done;
{
	DB *dbp;
	HASH_CURSOR *hcp;
	db_pgno_t origpgno, pgno;
	int ret;

	hcp = (HASH_CURSOR *)dbc->internal;
	dbp = dbc->dbp;
	memcpy(&pgno,
	    HOFFPAGE_PGNO(P_ENTRY(dbp, hcp->page, indx)), sizeof(db_pgno_t));
	if (pgno > c_data->compact_truncate) {
		c_data->compact_pages_examine++;
		origpgno = pgno;
		if ((ret = __memp_dirty(dbp->mpf, &hcp->page,
		    dbc->thread_info, dbc->txn, dbc->priority, 0)) != 0)
			return (ret);
		if ((ret = __db_truncate_root(dbc,
		    hcp->page, indx, &pgno, 0, pgs_done)) != 0)
			return (ret);
		if (pgno != origpgno) {
			memcpy(HOFFPAGE_PGNO(P_ENTRY(dbp, hcp->page, indx)),
			    &pgno, sizeof(db_pgno_t));
			(*pgs_done)++;
			c_data->compact_pages--;
		}
	}
	if ((ret =
	    __db_truncate_overflow(dbc, pgno, NULL, c_data, pgs_done)) != 0)
		return (ret);
	return (0);
}
