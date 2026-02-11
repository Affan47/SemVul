gc_db_set_board_conf(GcomprisProfile *profile,
		     GcomprisBoard  *board,
		     gchar *key,
		     gchar *value)
{
  SUPPORT_OR_RETURN(FALSE);

#ifdef USE_SQLITE
  char *zErrMsg;
  char **result;
  int rc;
  int nrow;
  int ncolumn;
  gchar *request;

  request = sqlite3_mprintf(CHECK_CONF,
			    profile->profile_id,
			    board->board_id,
			    key);

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

  sqlite3_free(request);

  if (nrow == 0){
    request = sqlite3_mprintf(INSERT_KEY,
			      profile->profile_id,
			      board->board_id,
			      key,
			      value);

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

    sqlite3_free(request);
  } else {
    request = sqlite3_mprintf(UPDATE_KEY,
			      value,
			      profile->profile_id,
			      board->board_id,
			      key
			      );

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

    sqlite3_free(request);
  }

  return TRUE;
#endif
}
