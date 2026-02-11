close_database(DB_DATABASE * db)
{
	SqliteDatabase *conn = (SqliteDatabase *) db->handle;

	if (conn)
	{
		conn->disconnect();
		delete conn;
	}
}
