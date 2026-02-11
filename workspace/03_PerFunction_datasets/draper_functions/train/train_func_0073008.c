unity_webapps_url_db_lookup_urls (UnityWebappsUrlDB *url_db, const gchar *url,
				  GList **out_records)
{
  GList *records;
  sqlite3_stmt *url_statement;
  int rc;
  gboolean ret = TRUE;

  *out_records = records = NULL;

  url_statement = unity_webapps_url_db_lookup_urls_prepare_statement (url_db, url);

  if (url_statement == NULL)
    {
      return FALSE;
    }

  do {
    const gchar *package_name;
    const gchar *app_name;
    const gchar *app_domain;
    rc = sqlite3_step (url_statement);

    if (rc != SQLITE_ROW)
      {
	continue;
      }

    package_name = (const gchar *)sqlite3_column_text (url_statement, 0);
    app_name = (const gchar *)sqlite3_column_text (url_statement, 1);
    app_domain = (const gchar *)sqlite3_column_text (url_statement, 2);
    records = g_list_append (records, unity_webapps_url_db_record_new (package_name, app_name, app_domain));
  } while (rc == SQLITE_ROW);

  if (rc != SQLITE_DONE)
    {
      ret = FALSE;
    }

  sqlite3_finalize (url_statement);
  *out_records = records;

  return ret;
}
