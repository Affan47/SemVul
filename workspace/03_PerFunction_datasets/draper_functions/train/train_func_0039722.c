logview_prefs_get_stored_window_size (LogviewPrefs *prefs,
                                      int *width, int *height)
{
  g_assert (LOGVIEW_IS_PREFS (prefs));

  *width = g_settings_get_int (prefs->priv->logview_prefs,
                               PREF_WIDTH);
  *height = g_settings_get_int (prefs->priv->logview_prefs,
                                PREF_HEIGHT);

  if ((*width == 0) ^ (*height == 0)) {

    *width = LOGVIEW_DEFAULT_WIDTH;
    *height = LOGVIEW_DEFAULT_HEIGHT;
  }
}
