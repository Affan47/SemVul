sql_finish_query(SQLSOCK * sqlsocket, UNUSED SQL_CONFIG *config)
{
#if (MYSQL_VERSION_ID >= 40100)
	rlm_sql_mysql_sock *mysql_sock = sqlsocket->conn;
	int status;

skip_next_result:
	status = sql_store_result(sqlsocket, config);
	if (status != 0) {
		return status;
	} else if (mysql_sock->result != NULL) {
		radlog(L_DBG, "rlm_sql_mysql: SQL statement returned unexpected result");
		sql_free_result(sqlsocket, config);
	}
	status = mysql_next_result(mysql_sock->sock);
	if (status == 0) {

		goto skip_next_result;
	}  else if (status > 0) {
		radlog(L_ERR, "rlm_sql_mysql: Cannot get next result");
		radlog(L_ERR, "rlm_sql_mysql: MySQL error '%s'",
		       mysql_error(mysql_sock->sock));
		return sql_check_error(status);
	}
#endif
	return 0;
}
