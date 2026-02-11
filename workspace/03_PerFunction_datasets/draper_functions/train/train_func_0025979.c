CDB___db_traverse_big(dbp, pgno, callback, cookie)
	DB *dbp;
	db_pgno_t pgno;
	int (*callback) __P((DB *, PAGE *, void *, int *));
	void *cookie;
{
	PAGE *p;
	int did_put, ret;

	do {
		did_put = 0;
		if ((ret = CDB_memp_fget(dbp->mpf, &pgno, 0, &p)) != 0)
			return (ret);
		pgno = NEXT_PGNO(p);
		if ((ret = callback(dbp, p, cookie, &did_put)) == 0 &&
		    !did_put)
			ret = CDB_memp_fput(dbp->mpf, p, 0);
	} while (ret == 0 && pgno != PGNO_INVALID);

	return (ret);
}
