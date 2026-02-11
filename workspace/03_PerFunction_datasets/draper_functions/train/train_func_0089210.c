__db_get_cachesize(dbp, cache_gbytesp, cache_bytesp, ncachep)
	DB *dbp;
	u_int32_t *cache_gbytesp, *cache_bytesp;
	int *ncachep;
{
	DB_ILLEGAL_IN_ENV(dbp, "DB->get_cachesize");

	return (__memp_get_cachesize(dbp->dbenv,
	    cache_gbytesp, cache_bytesp, ncachep));
}
