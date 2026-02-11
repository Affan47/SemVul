__bamc_compress_put(dbc, key, data, flags)
	DBC *dbc;
	DBT *key, *data;
	u_int32_t flags;
{
	DBC *dbc_n;
	int ret, t_ret;

	if (F_ISSET((BTREE_CURSOR *)dbc->internal, C_COMPRESS_MODIFIED)) {
		if ((flags & DB_OPFLAGS_MASK) == DB_CURRENT &&
		    (ret = __bamc_compress_relocate(dbc)) != 0)
			return (ret);
		F_CLR((BTREE_CURSOR *)dbc->internal, C_COMPRESS_MODIFIED);
	}

	if (F_ISSET(dbc, DBC_TRANSIENT))
		dbc_n = dbc;
	else {
		if ((ret = __dbc_dup(dbc, &dbc_n,
		    (flags & DB_OPFLAGS_MASK) == DB_CURRENT ?
		    DB_POSITION : 0)) != 0)
			goto err;


		F_SET(dbc_n, DBC_TRANSIENT);
	}

	if ((ret = __bamc_compress_iput(dbc_n, key, data, flags)) != 0)
		goto err;

err:

	if ((t_ret = __dbc_cleanup(dbc, dbc_n, ret)) != 0 &&
		(ret == 0 || ret == DB_BUFFER_SMALL))
		ret = t_ret;
	return (ret);
}
