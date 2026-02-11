gdict_window_ensure_menu_state (GdictWindow *window)
{
  gint i;
  gboolean is_enabled;

  g_assert (GDICT_IS_WINDOW (window));

  is_enabled = !!(window->word != NULL);
  for (i = 0; i < n_toggle_state; i++)
    {
      GAction *action;

      action = g_action_map_lookup_action (G_ACTION_MAP (window),
                                           toggle_actions[i]);
      if (!action)
        continue;

      g_simple_action_set_enabled (G_SIMPLE_ACTION (action), is_enabled);
    }
}
