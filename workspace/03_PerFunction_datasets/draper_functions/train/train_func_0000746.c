conf_ok(GHashTable *table)
{
  if (!table){
    if (gcomprisBoard)
      pause_board(FALSE);
    return;
  }

  g_hash_table_foreach(table, (GHFunc) save_table, NULL);

  if (gcomprisBoard){
    GHashTable *config;

    if (profile_conf)
      config = gc_db_get_board_conf();
    else
      config = table;

    if (strcmp(gcomprisBoard->name, "imagename")==0){
      gc_locale_set(g_hash_table_lookup( config, "locale"));
    }

    gchar *drag_mode_str = g_hash_table_lookup( config, "drag_mode");

    if (drag_mode_str && (strcmp (drag_mode_str, "NULL") != 0))
      drag_mode = (gint ) g_ascii_strtod(drag_mode_str, NULL);
    else
      drag_mode = 0;

    if (profile_conf)
      g_hash_table_destroy(config);

    gc_drag_change_mode( drag_mode);

    shapegame_next_level();

    pause_board(FALSE);
  }

  board_conf = NULL;
  profile_conf = NULL;

}
