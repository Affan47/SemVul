timeout_cb (void *data)
{
  gint sp;

  animate_game_graphics ();

  clear_game_area ();

  if ((game_state == STATE_TYPE2) || (game_state == STATE_WTYPE2)) {
    move_type2_robots ();
    update_arena ();
    if (game_state == STATE_TYPE2) {
      game_state = STATE_PLAYING;
    } else if (game_state == STATE_WTYPE2) {
      game_state = STATE_WAITING;
    }
  } else if (game_state == STATE_WAITING) {
    remove_splat_bubble ();
    move_robots ();
  } else if (game_state == STATE_COMPLETE) {
    ++endlev_counter;
    if (endlev_counter >= CHANGE_DELAY) {
      ++current_level;
      remove_bubble ();
      reset_player_animation ();
      clear_game_area ();
      generate_level ();
      game_state = STATE_PLAYING;
      set_move_menu_sensitivity (TRUE);
      gnobots_statusbar_set (score, current_level + 1, safe_teleports,
                             num_robots1, num_robots2);
    }
  } else if (game_state == STATE_DEAD) {
    ++endlev_counter;
    if (endlev_counter >= DEAD_DELAY) {
      if (score > 0) {
        sp = log_score (score);
        if (show_scores (sp, TRUE) == GTK_RESPONSE_REJECT) {
          quit_game ();
        }
      }
      start_new_game ();
    }
  }

  return TRUE;
}
