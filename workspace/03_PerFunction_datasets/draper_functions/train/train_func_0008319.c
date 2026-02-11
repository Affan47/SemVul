stream_resolve (GrlSourceResolveSpec *rs)
{
  gint r;
  sqlite3_stmt *sql_stmt = NULL;
  sqlite3 *db;
  GError *error = NULL;
  gchar *sql;
  const gchar *id;

  GRL_DEBUG (__FUNCTION__);

  db = GRL_PODCASTS_SOURCE (rs->source)->priv->db;

  id = grl_media_get_id (rs->media);
  sql = g_strdup_printf (GRL_SQL_GET_PODCAST_STREAM, id);
  GRL_DEBUG ("%s", sql);
  r = sqlite3_prepare_v2 (db, sql, strlen (sql), &sql_stmt, NULL);
  g_free (sql);

  if (r != SQLITE_OK) {
    GRL_WARNING ("Failed to get podcast stream: %s", sqlite3_errmsg (db));
    error = g_error_new_literal (GRL_CORE_ERROR,
                                 GRL_CORE_ERROR_RESOLVE_FAILED,
                                 _("Failed to get podcast stream metadata"));
    rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, error);
    g_error_free (error);
    return;
  }

  while ((r = sqlite3_step (sql_stmt)) == SQLITE_BUSY);

  if (r == SQLITE_ROW) {
    build_media_from_stmt (rs->media, sql_stmt, FALSE);
    rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, NULL);
  } else {
    GRL_WARNING ("Failed to get podcast stream: %s", sqlite3_errmsg (db));
    error = g_error_new_literal (GRL_CORE_ERROR,
                                 GRL_CORE_ERROR_RESOLVE_FAILED,
                                 _("Failed to get podcast stream metadata"));
    rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, error);
    g_error_free (error);
  }

  sqlite3_finalize (sql_stmt);
}
