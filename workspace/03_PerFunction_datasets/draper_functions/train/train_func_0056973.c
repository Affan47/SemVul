sql_close(SQLSOCK * sqlsocket, UNUSED SQL_CONFIG *config)
{
	rlm_sql_mysql_sock *mysql_sock = sqlsocket->conn;

	if (mysql_sock && mysql_sock->sock){
		mysql_close(mysql_sock->sock);
		mysql_sock->sock = NULL;
	}

	return 0;
}
