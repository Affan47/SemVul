config_start(GcomprisBoard *agcomprisBoard,
	     GcomprisProfile *aProfile)
{
  board_conf = agcomprisBoard;
  profile_conf = aProfile;

  if (gcomprisBoard)
    pause_board(TRUE);

  gchar * label = g_strdup_printf(_("<b>%s</b> configuration\n for profile <b>%s</b>"),
				  agcomprisBoard->name,
				  aProfile? aProfile->name : "");

  GcomprisBoardConf *bconf;
  bconf = gc_board_config_window_display( label,
					  conf_ok);

  g_free(label);


  GHashTable *config = gc_db_get_conf( profile_conf, board_conf);

  gchar *drag_mode_str = g_hash_table_lookup( config, "drag_mode");
  gint drag_previous;

  if (drag_mode_str && (strcmp (drag_mode_str, "NULL") != 0))
    drag_previous = (gint ) g_ascii_strtod(drag_mode_str, NULL);
  else
    drag_previous = 0;

  gc_board_config_combo_drag(bconf, drag_previous);

}
