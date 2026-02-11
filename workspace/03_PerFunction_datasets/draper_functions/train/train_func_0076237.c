CDB___db_des_destroy(dbenv, rp)
	DB_ENV *dbenv;
	REGION *rp;
{
	REGINFO *infop;


	infop = dbenv->reginfo;

	SH_LIST_REMOVE(rp, q, __db_region);
	CDB___db_shalloc_free(infop->addr, rp);

	return (0);
}
