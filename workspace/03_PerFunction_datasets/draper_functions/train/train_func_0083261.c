start_new_game (void)
{
  GameConfig *conf;
  current_level = 0;
  score = 0;
  kills = 0;
  score_step = 0;

  if (game_state == STATE_PLAYING)
    log_score (score);

  conf = game_config ();
  g_return_if_fail (conf != NULL);

  safe_teleports = conf->initial_safe_teleports;

  remove_bubble ();
  reset_player_animation ();
  generate_level ();
  clear_game_area ();

  if (game_config ()->maximum_type2 > 0) {
    gnobots_statusbar_show_both (TRUE);
  } else {
    gnobots_statusbar_show_both (FALSE);
  }

  game_state = STATE_PLAYING;

  gnobots_statusbar_set (score, current_level + 1, safe_teleports,
                         num_robots1, num_robots2);
  set_move_menu_sensitivity (TRUE);
}
