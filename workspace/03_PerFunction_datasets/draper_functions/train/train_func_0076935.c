conf_value_changed_cb (GSettings *settings, gchar *key)
{
  if (strcmp (key, KEY_BACKGROUND_COLOR) == 0) {
    gchar *color;

    color = g_settings_get_string (settings, KEY_BACKGROUND_COLOR);
    if (color != NULL) {
      set_backgnd_color (color);
      g_free (color);
    }
  } else if (strcmp (key, KEY_BALL_THEME) == 0) {
    gchar *theme_tmp = NULL;

    theme_tmp = g_settings_get_string (settings, KEY_BALL_THEME);
    if (theme_tmp) {
      if (strcmp (theme_tmp, ball_filename) != 0) {
        g_free (ball_filename);
        ball_filename = theme_tmp;
        load_theme ();
        refresh_screen ();
      } else
        g_free (theme_tmp);
    }

  } else if (strcmp (key, KEY_MOVE_TIMEOUT) == 0) {
    gint timeout_tmp;

    timeout_tmp = g_settings_get_int (settings, KEY_MOVE_TIMEOUT);
    timeout_tmp = CLAMP (timeout_tmp, 1, 1000);
    if (timeout_tmp != move_timeout)
      move_timeout = timeout_tmp;

  } else if (strcmp (key, KEY_SIZE) == 0) {
    gint size_tmp;
    size_tmp = g_settings_get_int (settings, KEY_SIZE);

    if (size_tmp != game_size) {
      set_sizes (size_tmp);
      reset_game ();
      start_game ();
    }
  }
}
