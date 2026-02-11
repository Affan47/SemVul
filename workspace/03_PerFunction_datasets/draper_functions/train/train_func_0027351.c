__dbc_put_resolve_key(dbc, oldkey, olddata, put_statep, flags)
	DBC *dbc;
	DBT *oldkey, *olddata;
	u_int32_t flags, *put_statep;
{
	DB *dbp;
	ENV *env;
	int ret, rmw;

	dbp = dbc->dbp;
	env = dbp->env;
	rmw = FLD_ISSET(*put_statep, DBC_PUT_RMW) ? DB_RMW : 0;

	DB_ASSERT(env, flags == DB_CURRENT);
	COMPQUIET(flags, 0);


	memset(oldkey, 0, sizeof(DBT));
	if ((ret = __dbc_get(dbc, oldkey, olddata, rmw | DB_CURRENT)) != 0)
		return (ret == DB_KEYEMPTY ? DB_NOTFOUND : ret);


	FLD_SET(*put_statep, DBC_PUT_HAVEREC);
	return (0);
}
