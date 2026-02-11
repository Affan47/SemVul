config_start(GcomprisBoard *agcomprisBoard,
	     GcomprisProfile *aProfile)
{
  board_conf = agcomprisBoard;
  profile_conf = aProfile;

  if (gcomprisBoard)
    pause_board(TRUE);

  gchar * label = g_strdup_printf(_("<b>%1$s</b> configuration\n for profile <b>%2$s</b>"),
				  agcomprisBoard->name,
				  aProfile? aProfile->name : "");

  GcomprisBoardConf *bconf;
  bconf = \
    gc_board_config_window_display( label,
				    (GcomprisConfCallback )conf_ok);

  g_free(label);


  GHashTable *config = gc_db_get_conf( profile_conf, board_conf);

  if (strcmp(agcomprisBoard->name, "imagename")==0){
    gchar *locale = g_hash_table_lookup( config, "locale");

    gc_board_config_combo_locales( bconf, locale);
  }

  gchar *drag_mode_str = g_hash_table_lookup( config, "drag_mode");
  gint drag_previous;

  if (drag_mode_str && (strcmp (drag_mode_str, "NULL") != 0))
    drag_previous = (gint ) g_ascii_strtod(drag_mode_str, NULL);
  else
    drag_previous = 0;

  gc_board_config_combo_drag(bconf, drag_previous);

}
