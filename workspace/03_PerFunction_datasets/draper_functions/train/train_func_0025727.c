__db_stream_read(dbs, data, offset, size, flags)
	DB_STREAM *dbs;
	DBT *data;
	db_off_t offset;
	u_int32_t size;
	u_int32_t flags;
{
	DBC *dbc;
	ENV *env;
	int ret;
	u_int32_t needed, start;

	dbc = dbs->dbc;
	env = dbc->dbp->env;
	ret = 0;

	if ((ret = __db_fchk(env, "DB_STREAM->read", flags, 0)) != 0)
		return (ret);

	if (F_ISSET(data, DB_DBT_PARTIAL)) {
		ret = EINVAL;
		__db_errx(env, DB_STR("0212",
		    "Error, do not use DB_DBT_PARTIAL with DB_STREAM."));
		goto err;
	}

	if (offset > dbs->file_size) {
		data->size = 0;
		goto err;
	}

	if ((ret = __db_alloc_dbt(
	    env, data, size, &needed, &start, NULL, NULL)) != 0)
		goto err;
	data->size = needed;

	if (needed == 0)
		goto err;

	ret = __blob_file_read(env, dbs->fhp, data, offset, size);

err:	return (ret);
}
