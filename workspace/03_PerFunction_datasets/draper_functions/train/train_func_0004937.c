__ham_item_reset(dbc)
	DBC *dbc;
{
	DB *dbp;
	DB_MPOOLFILE *mpf;
	HASH_CURSOR *hcp;
	int ret, t_ret;

	dbp = dbc->dbp;
	mpf = dbp->mpf;
	hcp = (HASH_CURSOR *)dbc->internal;

	ret = 0;
	if (hcp->page != NULL) {
		ret = __memp_fput(mpf,
		    dbc->thread_info, hcp->page, dbc->priority);
		hcp->page = NULL;
	}

	if ((t_ret = __ham_item_init(dbc)) != 0 && ret == 0)
		ret = t_ret;

	return (ret);
}
