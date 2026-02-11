db_init(dbenv, home, is_salvage, cache, is_privatep)
	DB_ENV *dbenv;
	char *home;
	int is_salvage;
	u_int32_t cache;
	int *is_privatep;
{
	int ret;


	*is_privatep = 0;
	if ((ret = dbenv->open(dbenv, home,
	    DB_USE_ENVIRON | (is_salvage ? DB_INIT_MPOOL : 0), 0)) == 0)
		return (0);
	if (ret == DB_VERSION_MISMATCH || ret == DB_REP_LOCKOUT)
		goto err;


	*is_privatep = 1;
	if ((ret = dbenv->set_cachesize(dbenv, 0, cache, 1)) == 0 &&
	    (ret = dbenv->open(dbenv, home,
	    DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE | DB_USE_ENVIRON, 0)) == 0)
		return (0);


err:	dbenv->err(dbenv, ret, "DB_ENV->open");
	return (1);
}
