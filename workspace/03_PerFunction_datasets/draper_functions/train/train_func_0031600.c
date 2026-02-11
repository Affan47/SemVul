database_exist(DB_DATABASE * db, const char *name)
{
	SqliteDatabase *conn = (SqliteDatabase *) db->handle;
	char *fullpath = NULL;

	if (strcmp(name, ":memory:") == 0)
		return TRUE;

	if ((fullpath = FindDatabase(name, conn->getHostName())) != NULL)
	{
		GB.FreeString(&fullpath);
		return TRUE;
	}

	GB.FreeString(&fullpath);
	return FALSE;
}
