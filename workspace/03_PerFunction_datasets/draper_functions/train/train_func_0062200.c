CDB___ham_groupalloc_recover(dbenv, dbtp, lsnp, redo, info)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	int redo;
	void *info;
{
	__ham_groupalloc_args *argp;
	DBMETA *mmeta;
	DB_MPOOLFILE *mpf;
	DB *file_dbp;
	DBC *dbc;
	PAGE *pagep;
	db_pgno_t pgno;
	int cmp_n, cmp_p, modified, ret;

	modified = 0;
	COMPQUIET(info, NULL);
	REC_PRINT(CDB___ham_groupalloc_print);
	REC_INTRO(CDB___ham_groupalloc_read, 0);

	if ((ret = CDB_memp_fget(mpf, &argp->pgno, 0, &pagep)) != 0) {
		if (redo) {

			(void)CDB___db_pgerr(file_dbp, argp->pgno);
			goto out;
		} else {
			ret = 0;
			goto done;
		}
	}

	cmp_n = CDB_log_compare(lsnp, &LSN(pagep));
	cmp_p = CDB_log_compare(&LSN(pagep), &argp->metalsn);

	if (cmp_p == 0 && redo) {
		LSN(pagep) = *lsnp;
		modified = 1;
	} else if (cmp_n == 0 && !redo) {
		LSN(pagep) = argp->metalsn;
		modified = 1;
	}


	if (redo) {
		if ((ret = CDB___ham_alloc_pages(file_dbp,
		    (HMETA *)pagep, argp->start_pgno, argp->num)) != 0)
			goto out1;


		if (argp->pgno != PGNO_BASE_MD) {
			pgno = PGNO_BASE_MD;
			if ((ret = CDB_memp_fget(mpf, &pgno, 0, &mmeta)) != 0)
				goto out1;
			mmeta->lsn = *lsnp;
			if ((ret = CDB_memp_fput(mpf, mmeta, DB_MPOOL_DIRTY)) != 0)
				goto out1;
		}
	}


	if (!redo && argp->pgno != PGNO_BASE_MD) {
		if ((ret = CDB___ham_free_pages(file_dbp, argp)) != 0)
			goto out1;
		LSN(pagep) = argp->metalsn;
		modified = 1;
	}

out1:	if ((ret = CDB_memp_fput(mpf, pagep, modified ? DB_MPOOL_DIRTY : 0)) != 0)
		goto out;

done:	if (ret == 0)
		*lsnp = argp->prev_lsn;

out:	REC_CLOSE;
}
