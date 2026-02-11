__bam_irep_recover(env, dbtp, lsnp, op, info)
	ENV *env;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops op;
	void *info;
{
	__bam_irep_args *argp;
	BINTERNAL *bn;
	DB_THREAD_INFO *ip;
	DB *file_dbp;
	DBC *dbc;
	DB_MPOOLFILE *mpf;
	PAGE *pagep;
	int cmp_n, cmp_p, ret;

	ip = ((DB_TXNHEAD *)info)->thread_info;
	pagep = NULL;
	REC_PRINT(__bam_irep_print);
	REC_INTRO(__bam_irep_read, ip, 1);


	if ((ret = __memp_fget(mpf, &argp->pgno, ip, NULL, 0, &pagep)) != 0) {
		if (ret != DB_PAGE_NOTFOUND) {
			ret = __db_pgerr(file_dbp, argp->pgno, ret);
			goto out;
		} else
			goto done;
	}

	cmp_n = LOG_COMPARE(lsnp, &LSN(pagep));
	cmp_p = LOG_COMPARE(&LSN(pagep), &argp->lsn);
	CHECK_LSN(env, op, cmp_p, &LSN(pagep), &argp->lsn);
	CHECK_ABORT(env, op, cmp_n, &LSN(pagep), lsnp);
	if (cmp_p == 0 && DB_REDO(op)) {
		REC_DIRTY(mpf, ip, dbc->priority, &pagep);
		bn = (BINTERNAL *)argp->hdr.data;
		if ((ret = __bam_ritem_nolog(dbc,
		    pagep, argp->indx, &argp->hdr, &argp->data, bn->type)) != 0)
			goto out;
		LSN(pagep) = *lsnp;
	} else if (cmp_n == 0 && DB_UNDO(op)) {
		REC_DIRTY(mpf, ip, dbc->priority, &pagep);
		bn = (BINTERNAL *)argp->old.data;
		if ((ret = __bam_ritem_nolog(dbc,
		    pagep, argp->indx, &argp->old, NULL, bn->type)) != 0)
			goto out;
		LSN(pagep) = argp->lsn;
	}

	if ((ret = __memp_fput(mpf, ip, pagep, dbc->priority)) != 0)
		goto out;
	pagep = NULL;

done:	*lsnp = argp->prev_lsn;
	ret = 0;

out:	if (pagep != NULL)
		(void)__memp_fput(mpf, ip, pagep, dbc->priority);
	REC_CLOSE;
}
