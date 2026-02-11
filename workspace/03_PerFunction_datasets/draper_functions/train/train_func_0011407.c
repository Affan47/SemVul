__bamc_compress_get_set(dbc, key, data, method, flags)
	DBC *dbc;
	DBT *key;
	DBT *data;
	u_int32_t method;
	u_int32_t flags;
{
	int ret, cmp;
	BTREE_CURSOR *cp;
	DB *dbp;

	cp = (BTREE_CURSOR *)dbc->internal;
	dbp = dbc->dbp;

	if (method == DB_SET || method == DB_SET_RANGE)
	    data = NULL;

	F_CLR(cp, C_COMPRESS_DELETED);

	ret = __bamc_compress_seek(dbc, key, data, flags);
	if (ret == DB_NOTFOUND)
		CMP_IGET_RETRY(ret, dbc,
		    &cp->key1, &cp->compressed, DB_FIRST | flags);
	if (ret != 0)
		return (ret);


	cmp = 0;
	ret = __bamc_start_decompress(dbc);
	while (ret == 0 && (cmp = __db_compare_both(dbp,
	   cp->currentKey, cp->currentData, key, data)) < 0) {
		ret = __bamc_next_decompress(dbc);
		if (ret == DB_NOTFOUND) {
			CMP_IGET_RETRY(ret, dbc,
			    &cp->key1, &cp->compressed, DB_NEXT | flags);
			if (ret == 0)
			    ret = __bamc_start_decompress(dbc);
		}
	}

	switch (method) {
	case DB_SET:
	case DB_GET_BOTH_RANGE:


		if (ret == 0 &&
		    __db_compare_both(dbp, cp->currentKey, 0, key, 0) != 0) {

			ret = DB_NOTFOUND;
		}
		break;
	case DB_GET_BOTH:
		if (ret == 0 && (cmp != 0 || (!F_ISSET(dbp, DB_AM_DUPSORT) &&
		    __bam_defcmp(dbp, cp->currentData, data, NULL) != 0))) {

			ret = DB_NOTFOUND;
		}
		break;
	default:
		DB_ASSERT(dbp->env, method == 0 || method == DB_SET_RANGE);
	}

	return (ret);
}
