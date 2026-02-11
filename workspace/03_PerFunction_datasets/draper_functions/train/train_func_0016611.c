start_board (GcomprisBoard *agcomprisBoard)
{
  GHashTable *config = gc_db_get_board_conf();

  locale_sound = g_strdup(g_hash_table_lookup( config, "locale_sound"));

  gchar *control_sound = g_hash_table_lookup( config, "with_sound");

  if (control_sound && strcmp(g_hash_table_lookup( config, "with_sound"),"True")==0)
    with_sound = TRUE;
  else
    with_sound = FALSE;

  g_hash_table_destroy(config);

  if(agcomprisBoard!=NULL)
    {
      gcomprisBoard=agcomprisBoard;


      gcomprisBoard->disable_im_context = TRUE;

      gc_set_background(goo_canvas_get_root_item(gcomprisBoard->canvas),
			"smallnumbers/scenery7_background.png");

      gcomprisBoard->level = 1;
      gcomprisBoard->maxlevel = 9;
      gcomprisBoard->number_of_sublevel=10;
      gc_score_start(SCORESTYLE_NOTE,
			   BOARDWIDTH - 195,
			   BOARDHEIGHT - 30,
			   gcomprisBoard->number_of_sublevel);
      gc_bar_set(GC_BAR_CONFIG|GC_BAR_LEVEL);


      number_of_dices=1;
      if(!gcomprisBoard->mode)
	number_of_dices=1;
      else if(g_ascii_strncasecmp(gcomprisBoard->mode, "2_DICES", 7)==0) {

	number_of_dices=2;
      }

      smallnumbers_next_level();

      gamewon = FALSE;
      pause_board(FALSE);
    }
}
