odbc_set_uint64(uint64_t *v, SQLHSTMT stmt, SQLUSMALLINT col,
		SQLLEN *indicator)
{
	SQLRETURN ret;
	SQLCHAR buf[33];

	if(v != NULL)
	{
		sprintf(buf, "%ju", *v);
		*indicator = SQL_NTS;
		ret = SQLBindParameter(stmt,
				col, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT,
				0, 0, v, 0, indicator);
	}
	else
	{
		buf[0] = 0;
		*indicator = SQL_NULL_DATA;
		ret = SQLBindParameter(stmt,
				col, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
				0, 0, buf, 0, indicator);
	}
	if(!SQL_SUCCEEDED(ret))
		return APR_EGENERAL;

	return APR_SUCCESS;
}
