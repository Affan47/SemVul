CDB___db_set_cachesize(dbp, cache_gbytes, cache_bytes, ncache)
	DB *dbp;
	u_int32_t cache_gbytes, cache_bytes;
	int ncache;
{
	DB_ILLEGAL_IN_ENV(dbp, "set_cachesize");
	DB_ILLEGAL_AFTER_OPEN(dbp, "set_cachesize");

	return (dbp->dbenv->set_cachesize(
	    dbp->dbenv, cache_gbytes, cache_bytes, ncache));
}
