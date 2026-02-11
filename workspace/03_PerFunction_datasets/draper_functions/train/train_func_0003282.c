__ham_getindex_unsorted(dbc, p, key, match, indx)
	DBC *dbc;
	PAGE *p;
	const DBT *key;
	int *match;
	db_indx_t *indx;
{
	DB *dbp;
	DBT pg_dbt;
	HASH *t;
	db_pgno_t pgno;
	int i, n, res, ret;
	u_int32_t tlen;
	u_int8_t *hk;

	dbp = dbc->dbp;
	n = NUM_ENT(p);
	t = dbp->h_internal;
	res = 1;


	for (i = 0; i < n; i+=2) {
		hk = H_PAIRKEY(dbp, p, i);
		switch (HPAGE_PTYPE(hk)) {
		case H_OFFPAGE:

			memcpy(&tlen, HOFFPAGE_TLEN(hk), sizeof(u_int32_t));
			if (tlen == key->size) {
				memcpy(&pgno,
				    HOFFPAGE_PGNO(hk), sizeof(db_pgno_t));
				if ((ret = __db_moff(dbc, key, pgno, tlen,
				    t->h_compare, &res, NULL)) != 0)
					return (ret);
			}
			break;
		case H_KEYDATA:
			if (t->h_compare != NULL) {
				DB_INIT_DBT(pg_dbt,
				    HKEYDATA_DATA(hk), key->size);
				if (t->h_compare(
				    dbp, key, &pg_dbt, NULL) != 0)
					break;
			} else if (key->size ==
			    LEN_HKEY(dbp, p, dbp->pgsize, i))
				res = memcmp(key->data, HKEYDATA_DATA(hk),
				    key->size);
			break;
		case H_DUPLICATE:
		case H_OFFDUP:


		default:
			return (__db_pgfmt(dbp->env, PGNO(p)));
		}
		if (res == 0)
			break;
	}
	*indx = i;
	*match = (res == 0 ? 0 : 1);
	return (0);
}
