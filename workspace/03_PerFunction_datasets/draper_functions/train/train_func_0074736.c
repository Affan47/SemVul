db_d_delete(void)
{
    dbToken token;
    dbCursor *cursor;
    int stat;


    DB_RECV_TOKEN(&token);
    cursor = (dbCursor *) db_find_token(token);
    if (cursor == NULL || !db_test_cursor_type_update(cursor)) {
	db_error("** not an update cursor **");
	DB_SEND_FAILURE();
	return DB_FAILED;
    }


    stat = db_driver_delete(cursor);


    if (stat != DB_OK) {
	DB_SEND_FAILURE();
	return DB_OK;
    }
    DB_SEND_SUCCESS();


    return DB_OK;
}
