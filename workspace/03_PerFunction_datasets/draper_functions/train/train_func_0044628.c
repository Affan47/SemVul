end_game (gboolean show_splash)
{
  if (main_id) {
    g_source_remove (main_id);
    main_id = 0;
  }

  if (keyboard_id) {
    g_signal_handler_disconnect (G_OBJECT (stage), keyboard_id);
    keyboard_id = 0;
  }

  if (add_bonus_id) {
    g_source_remove (add_bonus_id);
    add_bonus_id = 0;
  }

  if (dummy_id) {
    g_source_remove (dummy_id);
    dummy_id = 0;
  }

  if (restart_id) {
    g_source_remove (restart_id);
    restart_id = 0;
  }

  if (show_splash) {
    render_logo ();
    gtk_action_set_sensitive (pause_action, FALSE);
    gtk_action_set_sensitive (end_game_action, FALSE);
    gtk_action_set_sensitive (preferences_action, TRUE);
  }

  games_pause_action_set_is_paused (GAMES_PAUSE_ACTION (pause_action), FALSE);
}
