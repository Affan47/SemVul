conf_ok(GHashTable *table)
{
  if (!table){
    if (gcomprisBoard)
      pause_board(FALSE);

    return TRUE;
  }

  g_hash_table_foreach(table, (GHFunc) save_table, NULL);

  board_conf = NULL;
  profile_conf = NULL;

  if (gcomprisBoard){
    GHashTable *config;
    if (profile_conf)
      config = gc_db_get_board_conf();
    else
      config = table;

    gboolean has_error = FALSE;
    gtk_tree_model_foreach(GTK_TREE_MODEL(model), _check_errors, &has_error);


    if (has_error)
      return FALSE;


    gc_locale_set(g_hash_table_lookup(config, "locale_sound"));

    if (profile_conf)
      g_hash_table_destroy(config);

    guint ready = sounds_are_fine();


    gchar *old_levels = levels_to_desktop();
    create_levels_from_config_model();
    gchar *new_levels = levels_to_desktop();

    if ( gcomprisBoard->level > gcomprisBoard->maxlevel )
      gcomprisBoard->level = 1;

    if (strcmp(old_levels, new_levels) != 0)
      {

	gchar *filename = get_user_desktop_file();
	g_file_set_contents(filename, new_levels, -1, NULL);
	g_free(filename);
      }
    g_free(old_levels);
    g_free(new_levels);

    if(ready)
      {
	if(ready == OK)
	  click_on_letter_next_level();

	gamewon = FALSE;
	pause_board(FALSE);
      }

  }

  board_conf = NULL;
  profile_conf = NULL;
  return TRUE;
}
