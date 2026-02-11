db_stream(DbStream** dbsp, u_int32_t _flags)
{
	int ret;
	DBC *dbc = this;
	DB_STREAM *dbs = 0;

	ret = dbc->db_stream(dbc, &dbs, _flags);

	if (DB_RETOK_STD(ret))
		*dbsp = (DbStream*)dbs;
	else
		DB_ERROR(DbEnv::get_DbEnv(dbc->dbenv),
		    "Dbc::db_stream", ret, ON_ERROR_UNKNOWN);

	return (ret);
}
