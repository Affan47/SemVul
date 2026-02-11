gc_db_set_date(gchar *date)
{
  SUPPORT_OR_RETURN(FALSE);

#ifdef USE_SQLITE
  char *zErrMsg;
  char **result;
  int rc;
  int nrow;
  int ncolumn;
  gchar *request;

  request = g_strdup_printf(BOARDS_SET_DATE(date));
  rc = sqlite3_get_table(gcompris_db,
			 request,
			 &result,
			 &nrow,
			 &ncolumn,
			 &zErrMsg
			 );
  if( rc!=SQLITE_OK ){
    g_error("SQL error: %s\n", zErrMsg);
  }
  g_free(request);

  sqlite3_free_table(result);

  return TRUE;
#endif
}
