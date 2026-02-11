db_close_connection(db_state *state)
{
    int index;
    SQLRETURN result;
    diagnos diagnos;

    if (associated_result_set(state)) {
	clean_state(state);
    }

    result = SQLDisconnect(connection_handle(state));

    if (!sql_success(result)) {
	diagnos = get_diagnos(SQL_HANDLE_DBC, connection_handle(state), extended_errors(state));
	return encode_error_message(diagnos.error_msg, extended_error(state, diagnos.sqlState), diagnos.nativeError);
    }

    if(!sql_success(SQLFreeHandle(SQL_HANDLE_DBC,
				  connection_handle(state))))
	DO_EXIT(EXIT_FREE);
    if(!sql_success(SQLFreeHandle(SQL_HANDLE_ENV,
				  environment_handle(state))))
	DO_EXIT(EXIT_FREE);

    return encode_atom_message("ok");
}
