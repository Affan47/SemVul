close_database(DB_DATABASE *db)
{

#ifdef ODBC_DEBUG_HEADER
fprintf(stderr,"[ODBC][%s][%d]\n",__FILE__,__LINE__);
fprintf(stderr,"\tclose_database\n");
fflush(stderr);
#endif

	ODBC_CONN *conn = (ODBC_CONN *)db->handle;

	if (conn->odbcHandle)
		SQLDisconnect(conn->odbcHandle);
	else
		GB.Error("ODBC module internal error");

	if (conn->odbcHandle)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, conn->odbcHandle);
		conn->odbcHandle = NULL;
	}
	else
		GB.Error("ODBC module internal error");

	if (conn->odbcEnvHandle)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, conn->odbcEnvHandle);
		conn->odbcEnvHandle = NULL;
	}
	else
		GB.Error("ODBC module internal error");

	if (conn->dsn_name)
		free(conn->dsn_name);

	if (conn->user_name)
		free(conn->user_name);

	if (conn)
	{
		SQL_Handle_free(conn);
		db->handle = NULL;
	}
}
