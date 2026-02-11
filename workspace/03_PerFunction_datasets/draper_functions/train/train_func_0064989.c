handle_db_request(byte *reqstring, db_state *state)
{
    byte *args;
    byte request_id;


    request_id = reqstring[0];
    args = reqstring + sizeof(byte);

    switch(request_id) {
    case OPEN_CONNECTION:
	return db_connect(args, state);
    case CLOSE_CONNECTION:
	return db_close_connection(state);
    case COMMIT_TRANSACTION:
	if(args[0] == COMMIT) {
	    return db_end_tran((byte)SQL_COMMIT, state);
	} else {
	    return db_end_tran((byte)SQL_ROLLBACK, state);
	}
    case QUERY:
	return db_query(args, state);
    case SELECT_COUNT:
	return db_select_count(args, state);
    case SELECT:
	return db_select(args, state);
    case PARAM_QUERY:
	return db_param_query(args, state);
    case DESCRIBE:
	return db_describe_table(args, state);
    default:
	DO_EXIT(EXIT_FAILURE);
    }
}
