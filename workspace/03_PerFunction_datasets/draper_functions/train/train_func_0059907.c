IoSQLite3_changes(IoSQLite3 *self, IoObject *locals, IoMessage *m)
{


	if (!DATA(self)->db)
	{
		return IONUMBER(0);
	}

	return IONUMBER(sqlite3_changes(DATA(self)->db));
}
