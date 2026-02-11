__ham_curadj_recover(env, dbtp, lsnp, op, info)
	ENV *env;
	DBT *dbtp;
	DB_LSN *lsnp;
	db_recops op;
	void *info;
{
	__ham_curadj_args *argp;
	db_ham_curadj mode, hamc_mode;
	DB_THREAD_INFO *ip;
	DB_MPOOLFILE *mpf;
	DB *file_dbp;
	DBC *dbc;
	HASH_CURSOR *hcp;
	int ret;

	ip = ((DB_TXNHEAD *)info)->thread_info;
	REC_PRINT(__ham_curadj_print);
	REC_INTRO(__ham_curadj_read, ip, 1);

	if (op != DB_TXN_ABORT)
		goto done;

	mode = (db_ham_curadj)argp->add;


	switch (mode) {
	case DB_HAM_CURADJ_DEL:
		hamc_mode = DB_HAM_CURADJ_ADD;
		break;
	case DB_HAM_CURADJ_ADD:
		hamc_mode = DB_HAM_CURADJ_DEL;
		break;
	case DB_HAM_CURADJ_ADDMOD:
		hamc_mode = DB_HAM_CURADJ_DELMOD;
		break;
	case DB_HAM_CURADJ_DELMOD:
		hamc_mode = DB_HAM_CURADJ_ADDMOD;
		break;
	default:
		__db_errx(env, DB_STR("1122",
		    "Invalid flag in __ham_curadj_recover"));
		ret = EINVAL;
		goto out;
	}


	hcp = (HASH_CURSOR *)dbc->internal;
	hcp->pgno = argp->pgno;
	hcp->indx = argp->indx;
	hcp->dup_off = argp->dup_off;
	hcp->order = argp->order;
	if (mode == DB_HAM_CURADJ_DEL)
		F_SET(hcp, H_DELETED);
	(void)__hamc_update(dbc, argp->len, hamc_mode, argp->is_dup);

done:	*lsnp = argp->prev_lsn;
out:	REC_CLOSE;
}
