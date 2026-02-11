db_get_homepage_prepare_statement (const gchar *name, const gchar *domain)
{
  gchar *statement_sql;
  sqlite3_stmt *statement;
  gint rc;

  statement_sql = sqlite3_mprintf (GET_HOMEPAGE_SQL_TEMPLATE, name, domain);

  statement = NULL;

  rc = sqlite3_prepare_v2 (app_db, statement_sql, -1, &statement, NULL);

  if (rc != SQLITE_OK)
    {
      g_critical ("Failed to compile App DB get homepage statement: %s", sqlite3_errmsg (app_db));
    }

  sqlite3_free (statement_sql);

  return statement;
}
