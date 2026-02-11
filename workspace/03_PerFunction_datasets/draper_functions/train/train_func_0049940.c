__qam_meta2pgset(dbp, vdp, pgset)
	DB *dbp;
	VRFY_DBINFO *vdp;
	DB *pgset;
{
	DBC *dbc;
	PAGE *h;
	db_pgno_t first, last, pgno, pg_ext, stop;
	int ret, t_ret;
	u_int32_t i;

	ret = 0;
	h = NULL;
	if (vdp->last_recno <= vdp->first_recno)
		return (0);

	pg_ext = vdp->page_ext;

	first = QAM_RECNO_PAGE(dbp, vdp->first_recno);


	last = QAM_RECNO_PAGE(dbp, vdp->last_recno - 1);

	if (first == PGNO_INVALID || last == PGNO_INVALID)
		return (DB_VERIFY_BAD);

	pgno = first;
	if (first > last)
		stop = QAM_RECNO_PAGE(dbp, UINT32_MAX);
	else
		stop = last;


	if (pg_ext == 0) {
		for (pgno = first; pgno <= stop; pgno++)
			if ((ret = __db_vrfy_pgset_inc(
			    pgset, vdp->thread_info, vdp->txn, pgno)) != 0)
				break;
		if (first > last)
			for (pgno = 1; pgno <= last; pgno++)
				if ((ret = __db_vrfy_pgset_inc(pgset,
				    vdp->thread_info, vdp->txn, pgno)) != 0)
					break;

		return (ret);
	}

	if ((ret = __db_cursor(dbp, vdp->thread_info, NULL, &dbc, 0)) != 0)
		return (ret);


begin:	for (; pgno <= stop; pgno += pg_ext) {
		if ((ret = __qam_fget(dbc, &pgno, 0, &h)) != 0) {
			if (ret == ENOENT || ret == DB_PAGE_NOTFOUND) {
				ret = 0;
				continue;
			}
			goto err;
		}
		if ((ret = __qam_fput(dbc, pgno, h, dbp->priority)) != 0)
			goto err;

		for (i = 0; i < pg_ext && pgno + i <= last; i++)
			if ((ret = __db_vrfy_pgset_inc(
			    pgset, vdp->thread_info, vdp->txn, pgno + i)) != 0)
				goto err;


		if (pgno == first)
			pgno = pgno % pg_ext + 1;
	}

	if (first > last) {
		pgno = 1;
		first = last;
		stop = last;
		goto begin;
	}

err:
	if ((t_ret = __dbc_close(dbc)) != 0 && ret == 0)
		ret = t_ret;

	return (ret);
}
