CDB___qam_del_recover(dbenv, dbtp, lsnp, redo, info)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	int redo;
	void *info;
{
	__qam_del_args *argp;
	DB *file_dbp;
	DBC *dbc;
	DB_LOCK lock;
	DB_MPOOLFILE *mpf;
	QAMDATA *qp;
	QMETA *meta;
	QPAGE *pagep;
	db_pgno_t metapg;
	int cmp_n, modified, ret;

	COMPQUIET(info, NULL);
	REC_PRINT(CDB___qam_del_print);
	REC_INTRO(CDB___qam_del_read, 1);

	dbc->txn = argp->txnid;
	if ((ret = CDB_memp_fget(mpf, &argp->pgno, 0, &pagep)) != 0) {
		if (redo) {
			if ((ret = CDB_memp_fget(mpf,
			    &argp->pgno, DB_MPOOL_CREATE, &pagep)) != 0)
				goto out;
			pagep->pgno = argp->pgno;
	                pagep->type = P_QAMDATA;
		} else {
			*lsnp = argp->prev_lsn;
			ret = 0;
			goto out;
		}
	}

	modified = 0;
	cmp_n = CDB_log_compare(lsnp, &LSN(pagep));

	if (cmp_n > 0 && redo) {

		qp = QAM_GET_RECORD(file_dbp, pagep, argp->indx);
		F_CLR(qp, QAM_VALID);
		LSN(pagep) = *lsnp;
		modified = 1;
	} else if (cmp_n <= 0 && !redo) {

		metapg = ((QUEUE *)file_dbp->q_internal)->q_meta;
		if ((ret =
		    CDB___db_lget(dbc, 0, metapg, DB_LOCK_WRITE, 0, &lock)) != 0)
			return (ret);
		if ((ret = CDB_memp_fget(file_dbp->mpf, &metapg, 0, &meta)) != 0) {
			(void)__LPUT(dbc, lock);
			goto done;
		}
		if (argp->recno < meta->first_recno) {
			meta->first_recno = argp->recno;
			(void)CDB_memp_fput(file_dbp->mpf, meta, DB_MPOOL_DIRTY);
		} else
			(void)CDB_memp_fput(file_dbp->mpf, meta, 0);
		(void)__LPUT(dbc, lock);


		qp = QAM_GET_RECORD(file_dbp, pagep, argp->indx);
		F_SET(qp, QAM_VALID);
		LSN(pagep) = argp->lsn;
		modified = 1;
	}
	if ((ret = CDB_memp_fput(mpf, pagep, modified ? DB_MPOOL_DIRTY : 0)))
		goto out;

done:	*lsnp = argp->prev_lsn;
	ret = 0;

out:	REC_CLOSE;
}
