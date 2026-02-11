xkb_options_changed (GSettings *settings,
                     gchar     *key,
                     gpointer   data)
{
  GList *l;

  g_strfreev (current_xkb_options);
  current_xkb_options = g_settings_get_strv (settings, key);

  for (l = objects_list; l; l = l->next)
    reload_setting (CC_KEYBOARD_OPTION (l->data));
}
