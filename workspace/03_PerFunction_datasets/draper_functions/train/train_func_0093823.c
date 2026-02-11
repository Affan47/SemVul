db_d_fetch(void)
{
    dbToken token;
    dbCursor *cursor;
    int stat;
    int more;
    int position;


    DB_RECV_TOKEN(&token);
    DB_RECV_INT(&position);
    cursor = (dbCursor *) db_find_token(token);
    if (!valid_cursor(cursor, position)) {
	DB_SEND_FAILURE();
	return DB_FAILED;
    }


    stat = db_driver_fetch(cursor, position, &more);


    if (stat != DB_OK) {
	DB_SEND_FAILURE();
	return DB_OK;
    }
    DB_SEND_SUCCESS();


    DB_SEND_INT(more);
    if (more) {
	DB_SEND_TABLE_DATA(cursor->table);
    }

    return DB_OK;
}
