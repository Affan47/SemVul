__memp_region_size(env, reg_sizep, htab_bucketsp)
	ENV *env;
	roff_t *reg_sizep;
	u_int32_t *htab_bucketsp;
{
	DB_ENV *dbenv;
	roff_t reg_size, cache_size;
	u_int32_t pgsize;

	dbenv = env->dbenv;


	cache_size = (roff_t)dbenv->mp_gbytes * GIGABYTE + dbenv->mp_bytes;
	reg_size = cache_size / dbenv->mp_ncache;
	if (reg_sizep != NULL)
		*reg_sizep = reg_size;


	if (htab_bucketsp != NULL) {
		if (dbenv->mp_tablesize != 0)
			*htab_bucketsp = __db_tablesize(dbenv->mp_tablesize);
		else {
			if ((pgsize = dbenv->mp_pagesize) == 0)
				pgsize = MPOOL_DEFAULT_PAGESIZE;
			*htab_bucketsp = __db_tablesize(
				(u_int32_t)(reg_size / (2.5 * pgsize)));
		}
	}

}
