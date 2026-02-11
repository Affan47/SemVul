open_db (SoupCookieJar *jar)
{
	SoupCookieJarDBPrivate *priv =
		SOUP_COOKIE_JAR_DB_GET_PRIVATE (jar);

	char *error = NULL;

	if (sqlite3_open (priv->filename, &priv->db)) {
		sqlite3_close (priv->db);
		priv->db = NULL;
		g_warning ("Can't open %s", priv->filename);
		return TRUE;
	}

	if (sqlite3_exec (priv->db, "PRAGMA synchronous = OFF; PRAGMA secure_delete = 1;", NULL, NULL, &error)) {
		g_warning ("Failed to execute query: %s", error);
		sqlite3_free (error);
	}

	return FALSE;
}
