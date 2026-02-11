sql_fetch_row(SQLSOCK *sqlsocket, SQL_CONFIG *config) {
    rlm_sql_unixodbc_sock *unixodbc_sock = sqlsocket->conn;
    long err_handle;
    int state;

    sqlsocket->row = NULL;

    err_handle = SQLFetch(unixodbc_sock->stmt_handle);
    if(err_handle == SQL_NO_DATA_FOUND)
	return 0;
    if ((state = sql_state(err_handle, sqlsocket, config))) {
	if(state == SQL_DOWN)
	    radlog(L_INFO, "rlm_sql_unixodbc: rlm_sql will attempt to reconnect\n");
	return state;
    }
    sqlsocket->row = unixodbc_sock->row;
    return 0;
}
