db_insert(dbCursor * cursor)
{
    int ret_code;


    db__set_protocol_fds(cursor->driver->send, cursor->driver->recv);
    DB_START_PROCEDURE_CALL(DB_PROC_INSERT);


    DB_SEND_TOKEN(&cursor->token);
    DB_SEND_TABLE_DATA(cursor->table);


    DB_RECV_RETURN_CODE(&ret_code);

    if (ret_code != DB_OK)
	return ret_code;


    return DB_OK;
}
