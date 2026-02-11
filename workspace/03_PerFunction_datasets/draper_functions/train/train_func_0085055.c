__ham_onpage_replace(dbp, pagep, ndx, off, change, is_plus, dbt)
	DB *dbp;
	PAGE *pagep;
	u_int32_t ndx;
	int32_t off;
	u_int32_t change;
	int is_plus;
	DBT *dbt;
{
	db_indx_t i, *inp;
	int32_t len;
	size_t pgsize;
	u_int8_t *src, *dest;
	int zero_me;

	pgsize = dbp->pgsize;
	inp = P_INP(dbp, pagep);
	if (change != 0) {
		zero_me = 0;
		src = (u_int8_t *)(pagep) + HOFFSET(pagep);
		if (off < 0)
			len = inp[ndx] - HOFFSET(pagep);
		else if ((u_int32_t)off >=
		    LEN_HKEYDATA(dbp, pagep, pgsize, ndx)) {
			len = (int32_t)(HKEYDATA_DATA(P_ENTRY(dbp, pagep, ndx))
			    + LEN_HKEYDATA(dbp, pagep, pgsize, ndx) - src);
			zero_me = 1;
		} else
			len = (int32_t)(
			    (HKEYDATA_DATA(P_ENTRY(dbp, pagep, ndx)) + off) -
			    src);
		if (is_plus)
			dest = src - change;
		else
			dest = src + change;
		memmove(dest, src, (size_t)len);
		if (zero_me)
			memset(dest + len, 0, change);


		for (i = ndx; i < NUM_ENT(pagep); i++) {
			if (is_plus)
				inp[i] -= change;
			else
				inp[i] += change;
		}
		if (is_plus)
			HOFFSET(pagep) -= change;
		else
			HOFFSET(pagep) += change;
	}
	if (off >= 0)
		memcpy(HKEYDATA_DATA(P_ENTRY(dbp, pagep, ndx)) + off,
		    dbt->data, dbt->size);
	else
		memcpy(P_ENTRY(dbp, pagep, ndx), dbt->data, dbt->size);
}
