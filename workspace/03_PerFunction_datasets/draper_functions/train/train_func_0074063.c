produce_podcast_contents (OperationSpec *os)
{
  sqlite3_stmt *sql_stmt = NULL;
  sqlite3 *db;
  GError *error;
  gchar *url;

  GRL_DEBUG ("produce_podcast_contents");


  db = GRL_PODCASTS_SOURCE (os->source)->priv->db;
  sql_stmt = get_podcast_info (db, os->media_id);
  if (sql_stmt) {
    gchar *lr_str;
    GTimeVal lr;
    GTimeVal now;


    lr_str = (gchar *) sqlite3_column_text (sql_stmt, PODCAST_LAST_REFRESHED);
    GRL_DEBUG ("Podcast last-refreshed: '%s'", lr_str);
    g_time_val_from_iso8601 (lr_str ? lr_str : "", &lr);
    os->last_refreshed = lr.tv_sec;
    g_get_current_time (&now);
    now.tv_sec -= GRL_PODCASTS_SOURCE (os->source)->priv->cache_time;
    if (lr_str == NULL || now.tv_sec >= lr.tv_sec) {

      GRL_DEBUG ("Refreshing podcast '%s'...", os->media_id);
      url = g_strdup ((gchar *) sqlite3_column_text (sql_stmt, PODCAST_URL));
      read_url_async (GRL_PODCASTS_SOURCE (os->source), url, read_feed_cb, os);
      g_free (url);
    } else {

      produce_podcast_contents_from_db (os);
      g_slice_free (OperationSpec, os);
    }
    sqlite3_finalize (sql_stmt);
  } else {
    error = g_error_new_literal (GRL_CORE_ERROR,
                                 os->error_code,
                                 _("Failed to get podcast information"));
    os->callback (os->source, os->operation_id, NULL, 0, os->user_data, error);
    g_error_free (error);
    g_slice_free (OperationSpec, os);
  }
}
