CDB___bam_ca_dup(dbp, fpgno, first, fi, tpgno, ti)
	DB *dbp;
	db_pgno_t fpgno, tpgno;
	u_int32_t first, fi, ti;
{
	BTREE_CURSOR *cp;
	DBC *dbc;


	if (dbp->type == DB_RECNO)
		return;


	MUTEX_THREAD_LOCK(dbp->mutexp);
	for (dbc = TAILQ_FIRST(&dbp->active_queue);
	    dbc != NULL; dbc = TAILQ_NEXT(dbc, links)) {
		cp = (BTREE_CURSOR *)dbc->internal;


		if (cp->dpgno == PGNO_INVALID &&
		    cp->pgno == fpgno && cp->indx == fi) {
			cp->indx = first;
			cp->dpgno = tpgno;
			cp->dindx = ti;
		}
	}
	MUTEX_THREAD_UNLOCK(dbp->mutexp);
}
