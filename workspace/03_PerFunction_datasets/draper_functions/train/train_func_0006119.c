ECPGstatus(int lineno, const char *connection_name)
{
	struct connection *con = ECPGget_connection(connection_name);

	if (!ECPGinit(con, connection_name, lineno))
		return (false);


	if (con->connection == NULL)
	{
		ECPGraise(lineno, ECPG_NOT_CONN, ECPG_SQLSTATE_ECPG_INTERNAL_ERROR, con->name);
		return false;
	}

	return (true);
}
