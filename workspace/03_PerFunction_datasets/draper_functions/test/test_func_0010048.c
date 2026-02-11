__bamc_compress_get(dbc, key, data, flags)
	DBC *dbc;
	DBT *key, *data;
	u_int32_t flags;
{
	DBC *dbc_n;
	int ret, t_ret;
	u_int32_t tmp_flags;

	switch (flags & DB_OPFLAGS_MASK) {
	case DB_CURRENT:
	case DB_GET_BOTHC:
	case DB_NEXT:
	case DB_NEXT_DUP:
	case DB_NEXT_NODUP:
	case DB_PREV:
	case DB_PREV_DUP:
	case DB_PREV_NODUP:
		if (F_ISSET((BTREE_CURSOR *)dbc->internal,
		    C_COMPRESS_MODIFIED) &&
		    (ret = __bamc_compress_relocate(dbc)) != 0)
			return (ret);
		tmp_flags = DB_POSITION;
		break;
	default:
		F_CLR((BTREE_CURSOR *)dbc->internal, C_COMPRESS_MODIFIED);
		tmp_flags = 0;
		break;
	}

	if (F_ISSET(dbc, DBC_TRANSIENT))
		dbc_n = dbc;
	else {
		if ((ret = __dbc_dup(dbc, &dbc_n, tmp_flags)) != 0)
			goto err;


		F_SET(dbc_n, DBC_TRANSIENT);

		COPY_RET_MEM(dbc, dbc_n);
	}

	if ((ret = __bamc_compress_iget(dbc_n, key, data, flags)) != 0)
		goto err;

err:

	if ((t_ret = __dbc_cleanup(dbc, dbc_n, ret)) != 0 &&
		(ret == 0 || ret == DB_BUFFER_SMALL))
		ret = t_ret;
	return (ret);
}
