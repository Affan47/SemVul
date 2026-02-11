__db_setup_freelist(dbp, list, nelems)
	DB *dbp;
	db_pglist_t *list;
	u_int32_t nelems;
{
	DB_MPOOLFILE *mpf;
	db_pgno_t *plist;
	int ret;

	mpf = dbp->mpf;

	if ((ret = __memp_alloc_freelist(mpf, nelems, &plist)) != 0)
		return (ret);

	while (nelems-- != 0)
		*plist++ = list++->pgno;

	return (0);
}
