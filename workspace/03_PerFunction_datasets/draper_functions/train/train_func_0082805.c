CDB___db_refresh(dbp)
	DB *dbp;
{
	DB_ENV *dbenv;
	int ret, t_ret;

	ret = 0;

	dbenv = dbp->dbenv;

	dbp->type = 0;


	if (dbp->mpf != NULL) {
		if (F_ISSET(dbp, DB_AM_DISCARD))
			(void)CDB___memp_fremove(dbp->mpf);
		if ((t_ret = CDB_memp_fclose(dbp->mpf)) != 0 && ret == 0)
			ret = t_ret;
		dbp->mpf = NULL;
	}


	if (dbp->mutexp != NULL) {
		CDB___db_mutex_free(dbenv, dbenv->reginfo, dbp->mutexp);
		dbp->mutexp = NULL;
	}


	if (dbp->log_fileid != DB_LOGFILEID_INVALID) {
		(void)CDB_log_unregister(dbenv, dbp->log_fileid);
		dbp->log_fileid = DB_LOGFILEID_INVALID;
	}

	TAILQ_INIT(&dbp->free_queue);
	TAILQ_INIT(&dbp->active_queue);

	F_CLR(dbp, DB_AM_DISCARD);
	F_CLR(dbp, DB_AM_INMEM);
	F_CLR(dbp, DB_AM_RDONLY);
	F_CLR(dbp, DB_AM_SWAP);
	F_CLR(dbp, DB_DBM_ERROR);
	F_CLR(dbp, DB_OPEN_CALLED);

	return (ret);
}
