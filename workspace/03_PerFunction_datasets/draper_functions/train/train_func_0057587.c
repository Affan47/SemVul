__bam_opd_cursor(dbp, dbc, first, tpgno, ti)
	DB *dbp;
	DBC *dbc;
	db_pgno_t tpgno;
	u_int32_t first, ti;
{
	BTREE_CURSOR *cp, *orig_cp;
	DBC *dbc_nopd;
	int ret;

	orig_cp = (BTREE_CURSOR *)dbc->internal;
	dbc_nopd = NULL;


	DB_ASSERT(dbp->env, orig_cp->opd == NULL);
	if ((ret = __dbc_newopd(dbc, tpgno, orig_cp->opd, &dbc_nopd)) != 0)
		return (ret);

	cp = (BTREE_CURSOR *)dbc_nopd->internal;
	cp->pgno = tpgno;
	cp->indx = ti;

	if (dbp->dup_compare == NULL) {


		cp->recno = ti + 1;
	}


	if (F_ISSET(orig_cp, C_DELETED)) {
		F_SET(cp, C_DELETED);
		F_CLR(orig_cp, C_DELETED);
	}


	orig_cp->opd = dbc_nopd;
	orig_cp->indx = first;
	return (0);
}
