__db_pageswap(env, dbp, pp, len, pdata, pgin)
	ENV *env;
	DB *dbp;
	void *pp;
	size_t len;
	DBT *pdata;
	int pgin;
{
	db_pgno_t pg;
	size_t pgsize;
	void *pgcopy;
	int ret;
	u_int16_t hoffset;

	switch (TYPE(pp)) {
	case P_BTREEMETA:
		return (__bam_mswap(env, pp));

	case P_HASHMETA:
		return (__ham_mswap(env, pp));

	case P_QAMMETA:
		return (__qam_mswap(env, pp));

	case P_INVALID:
	case P_OVERFLOW:
	case P_QAMDATA:


		pdata = NULL;
		break;

	default:
		break;
	}

	if (pgin) {
		P_32_COPYSWAP(&PGNO(pp), &pg);
		P_16_COPYSWAP(&HOFFSET(pp), &hoffset);
	} else {
		pg = PGNO(pp);
		hoffset = HOFFSET(pp);
	}

	if (pdata == NULL)
		ret = __db_byteswap(dbp, pg, (PAGE *)pp, len, pgin);
	else {
		pgsize = hoffset + pdata->size;
		if ((ret = __os_malloc(env, pgsize, &pgcopy)) != 0)
			return (ret);
		memset(pgcopy, 0, pgsize);
		memcpy(pgcopy, pp, len);
		memcpy((u_int8_t *)pgcopy + hoffset, pdata->data, pdata->size);

		ret = __db_byteswap(dbp, pg, (PAGE *)pgcopy, pgsize, pgin);
		memcpy(pp, pgcopy, len);


		if (!pgin) {
			if ((ret =
			    __os_malloc(env, pdata->size, &pdata->data)) != 0) {
				__os_free(env, pgcopy);
				return (ret);
			}
			F_SET(pdata, DB_DBT_APPMALLOC);
		}
		memcpy(pdata->data, (u_int8_t *)pgcopy + hoffset, pdata->size);
		__os_free(env, pgcopy);
	}

	return (ret);
}
