__dbc_put_partial(dbc, pkey, data, orig_data, out_data, put_statep, flags)
	DBC *dbc;
	DBT *pkey, *data, *orig_data, *out_data;
	u_int32_t *put_statep, flags;
{
	DB *dbp;
	DBC *pdbc;
	ENV *env;
	int ret, rmw, t_ret;

	dbp = dbc->dbp;
	env = dbp->env;
	ret = t_ret = 0;
	rmw = FLD_ISSET(*put_statep, DBC_PUT_RMW) ? DB_RMW : 0;

	if (!FLD_ISSET(*put_statep, DBC_PUT_HAVEREC) &&
	    !FLD_ISSET(*put_statep, DBC_PUT_NODEL)) {


		if ((ret = __dbc_idup(dbc, &pdbc, 0)) != 0)
			return (ret);


		DB_ASSERT(env, flags != DB_CURRENT);

		F_SET(pkey, DB_DBT_ISSET);
		ret = __dbc_get(pdbc, pkey, orig_data, rmw | DB_SET);
		if (ret == DB_KEYEMPTY || ret == DB_NOTFOUND) {
			FLD_SET(*put_statep, DBC_PUT_NODEL);
			ret = 0;
		}
		if ((t_ret = __dbc_close(pdbc)) != 0)
			ret = t_ret;
		if (ret != 0)
			return (ret);

		FLD_SET(*put_statep, DBC_PUT_HAVEREC);
	}

	COMPQUIET(flags, 0);


	return (__db_buildpartial(dbp, orig_data, data, out_data));
}
