__bam_ca_delete_func(dbc, my_dbc, countp, pgno, indx, args)
	DBC *dbc, *my_dbc;
	u_int32_t *countp;
	db_pgno_t pgno;
	u_int32_t indx;
	void *args;
{
	BTREE_CURSOR *cp;
	u_int32_t del;

	COMPQUIET(my_dbc, NULL);
	del = *(u_int32_t *)args;

	cp = (BTREE_CURSOR *)dbc->internal;
	if (cp->pgno == pgno && cp->indx == indx &&
	    !MVCC_SKIP_CURADJ(dbc, pgno)) {


		if (del) {
			F_SET(cp, C_DELETED);


			cp->stream_start_pgno = PGNO_INVALID;
		} else
			F_CLR(cp, C_DELETED);

#ifdef HAVE_COMPRESSION


		F_SET(cp, C_COMPRESS_MODIFIED);
#endif

		++(*countp);
	}
	return (0);
}
