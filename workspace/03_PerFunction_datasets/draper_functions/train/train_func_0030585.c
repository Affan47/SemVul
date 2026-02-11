__tuner_insert_kvpair(dbp, key_sz, data_sz, indx_pgsz, in_key, in_data, stats)
	DB *dbp;
	u_int32_t key_sz, data_sz;
	int indx_pgsz, in_key, in_data;
	TUNER_FF_STAT *stats;
{
	DB_ENV *dbenv;
	int is_big_data, is_big_key, ret;
	u_int32_t needed, pgsize;

	dbenv = dbp->dbenv;
	is_big_data = is_big_key = 0;
	needed = 0;
	pgsize = (1 << indx_pgsz) * DB_MIN_PGSIZE;

	if (key_sz > B_MINKEY_TO_OVFLSIZE(dbp, 2, pgsize))
		is_big_key = 1;

	if (data_sz > B_MINKEY_TO_OVFLSIZE(dbp, 2, pgsize))
		is_big_data = 1;

	if (is_big_key) {
		needed += BOVERFLOW_PSIZE;


		if ((ret =
		    __tuner_record_ovfl_pg(key_sz, indx_pgsz, stats)) != 0) {
			dbenv->err(dbenv, ret, "__tuner_record_ovfl_pg:key_sz");
			return (ret);
		}
	} else {


		if (in_key == INSERT_NOTHING)
			needed += 0;
		else if (in_key == INSERT_SLOT)
			needed += sizeof(db_indx_t);
		else if (in_key == INSERT_NORMAL)
			needed += BKEYDATA_PSIZE(key_sz);
	}

	if (is_big_data) {
		needed += BOVERFLOW_PSIZE;


		if ((ret =
		    __tuner_record_ovfl_pg(data_sz, indx_pgsz, stats)) != 0) {
			dbenv->err(dbenv, ret, "__tuner_record_ovfl_pg");
			return (ret);
		}
	} else {


		if (in_data == INSERT_NOTHING)
			needed += 0;
		else if (in_data == INSERT_BDUPLICATE)
			needed += BOVERFLOW_PSIZE;
		else if (in_data == INSERT_NORMAL)
			needed += BKEYDATA_PSIZE(data_sz);
	}

	if (needed == 0)
		return (EXIT_INSERT_ZERO_NEED);


	if (stats->pg_leaf_offset[indx_pgsz] == 0)
		stats->pg_leaf_offset[indx_pgsz] = SIZEOF_PAGE;

	if ((stats->pg_leaf_offset[indx_pgsz] + needed) > pgsize) {

		if ((ret = __tuner_record_leaf_pg(indx_pgsz, stats)) != 0) {
			dbenv->err(dbenv, ret, "__tuner_record_leaf_pg");
			return (ret);
		}


		stats->pg_leaf_offset[indx_pgsz] = needed + SIZEOF_PAGE;
	} else
		stats->pg_leaf_offset[indx_pgsz]  += needed;

	return (EXIT_SUCCESS);
}
