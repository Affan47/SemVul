CDB___qam_incfirst_recover(dbenv, dbtp, lsnp, redo, info)
	DB_ENV *dbenv;
	DBT *dbtp;
	DB_LSN *lsnp;
	int redo;
	void *info;
{
	__qam_incfirst_args *argp;
	DB *file_dbp;
	DBC *dbc;
	DB_LOCK lock;
	DB_MPOOLFILE *mpf;
	QMETA *meta;
	db_pgno_t metapg;
	int modified, ret;

	COMPQUIET(info, NULL);
	REC_PRINT(CDB___qam_incfirst_print);
	REC_INTRO(CDB___qam_incfirst_read, 1);

	metapg = ((QUEUE *)file_dbp->q_internal)->q_meta;

	dbc->txn = argp->txnid;
	if ((ret = CDB___db_lget(dbc, 0, metapg,  DB_LOCK_WRITE, 0, &lock)) != 0)
		goto done;
	if ((ret = CDB_memp_fget(mpf, &metapg, 0, &meta)) != 0) {
		if (redo) {
			if ((ret = CDB_memp_fget(mpf,
			    &metapg, DB_MPOOL_CREATE, &meta)) != 0) {
				(void)__LPUT(dbc, lock);
				goto out;
			}
			meta->dbmeta.pgno = metapg;
	                meta->dbmeta.type = P_QAMMETA;
		} else {
			*lsnp = argp->prev_lsn;
			ret = 0;
			(void)__LPUT(dbc, lock);
			goto out;
		}
	}

	modified = 0;


	if (!redo) {
		if (meta->first_recno > argp->recno) {
			meta->first_recno = argp->recno;
			modified = 1;
		}
	}


	if ((ret = CDB_memp_fput(mpf, meta, modified ? DB_MPOOL_DIRTY : 0)))
		goto out;

	(void)__LPUT(dbc, lock);

done:	*lsnp = argp->prev_lsn;
	ret = 0;

out:	REC_CLOSE;
}
