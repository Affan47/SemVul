gc_menu_load_db(GList *boards_list)
{
  SUPPORT_OR_RETURN(NULL);

#ifdef USE_SQLITE

  GList *boards = boards_list;

  char *zErrMsg;
  char **result;
  int rc;
  int nrow;
  int ncolumn;
  int i;

  rc = sqlite3_get_table(gcompris_db,
			 BOARDS_READ,
			 &result,
			 &nrow,
			 &ncolumn,
			 &zErrMsg
			 );

  if( rc!=SQLITE_OK ){
    g_error("SQL error: %s\n", zErrMsg);
  }


  i = ncolumn;

  while (i < (nrow +1)*ncolumn) {
    GcomprisBoard *gcomprisBoard = NULL;

    gcomprisBoard = g_malloc0 (sizeof (GcomprisBoard));

    gcomprisBoard->plugin=NULL;
    gcomprisBoard->previous_board=NULL;
    gcomprisBoard->board_ready=FALSE;
    gcomprisBoard->canvas=gc_get_canvas();

    gcomprisBoard->gmodule      = NULL;
    gcomprisBoard->gmodule_file = NULL;

    gcomprisBoard->board_id = atoi(result[i++]);
    gcomprisBoard->name = g_strdup(result[i++]);
    gcomprisBoard->section_id = atoi(result[i++]);
    gcomprisBoard->section = g_strdup(result[i++]);
    gcomprisBoard->author = g_strdup(result[i++]);
    gcomprisBoard->type = g_strdup(result[i++]);
    gcomprisBoard->mode = g_strdup(result[i++]);
    gcomprisBoard->difficulty = g_strdup(result[i++]);
    gcomprisBoard->icon_name = g_strdup(result[i++]);
    gcomprisBoard->boarddir = g_strdup(result[i++]);
    gcomprisBoard->mandatory_sound_file = g_strdup(result[i++]);
    gcomprisBoard->mandatory_sound_dataset = g_strdup(result[i++]);
    gcomprisBoard->filename = g_strdup(result[i++]);
    gcomprisBoard->title =  reactivate_newline(gettext(result[i++]));
    gcomprisBoard->description  = reactivate_newline(gettext(result[i++]));
    gcomprisBoard->prerequisite = reactivate_newline(gettext(result[i++]));
    gcomprisBoard->goal = reactivate_newline(gettext(result[i++]));
    gcomprisBoard->manual = reactivate_newline(gettext(result[i++]));
    gcomprisBoard->credit = reactivate_newline(gettext(result[i++]));
    gcomprisBoard->demo = atoi(result[i++]);

    boards = g_list_append(boards, gcomprisBoard);
    gchar *msg = g_strdup_printf(_("Loading activity from database:\n%s"),
				 gcomprisBoard->title);
    gc_status_set_msg(msg);
    g_free(msg);
  }

  sqlite3_free_table(result);

  return boards;

#endif
}
