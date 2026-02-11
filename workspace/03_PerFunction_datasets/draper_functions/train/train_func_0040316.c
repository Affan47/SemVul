camel_db_create_folders_table (CamelDB *cdb,
                               GError **error)
{
	const gchar *query = "CREATE TABLE IF NOT EXISTS folders ( "
		"folder_name TEXT PRIMARY KEY, "
		"version REAL, "
		"flags INTEGER, "
		"nextuid INTEGER, "
		"time NUMERIC, "
		"saved_count INTEGER, "
		"unread_count INTEGER, "
		"deleted_count INTEGER, "
		"junk_count INTEGER, "
		"visible_count INTEGER, "
		"jnd_count INTEGER, "
		"bdata TEXT )";
	CAMEL_DB_RELEASE_SQLITE_MEMORY;
	return ((camel_db_command (cdb, query, error)));
}
