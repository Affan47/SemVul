on_lockdown_settings_changed (GSettings     *settings,
                              const char    *key,
                              CcScreenPanel *panel)
{
  if (g_str_equal (key, "disable-lock-screen") == FALSE)
    return;

  update_lock_screen_sensitivity (panel);
}
