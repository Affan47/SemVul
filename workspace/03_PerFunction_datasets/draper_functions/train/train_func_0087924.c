__bam_ca_undosplit_func(dbc, my_dbc, foundp, frompgno, split_indx, vargs)
	DBC *dbc;
	DBC *my_dbc;
	u_int32_t *foundp;
	db_pgno_t frompgno;
	u_int32_t split_indx;
	void *vargs;
{
	DBC_INTERNAL *cp;
	struct __bam_ca_split_args *args;

	COMPQUIET(my_dbc, NULL);
	COMPQUIET(foundp, NULL);

	if (dbc->dbtype == DB_RECNO)
		return (0);
	cp = dbc->internal;
	args = vargs;
	if (cp->pgno == args->rpgno &&
	    !MVCC_SKIP_CURADJ(dbc, args->rpgno)) {
		cp->pgno = frompgno;
		cp->indx += split_indx;
	} else if (cp->pgno == args->lpgno &&
	    !MVCC_SKIP_CURADJ(dbc, args->lpgno))
		cp->pgno = frompgno;

	return (0);
}
