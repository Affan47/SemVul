terminal_window_save_state (TerminalWindow *window,
                            GKeyFile *key_file,
                            const char *group)
{
  TerminalWindowPrivate *priv = window->priv;
  GList *tabs, *lt;
  TerminalScreen *active_screen;
  GdkWindowState state;
  GPtrArray *tab_names_array;
  char **tab_names;
  gsize len;


  g_key_file_set_boolean (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_MENUBAR_VISIBLE,
                          priv->menubar_visible);

  g_key_file_set_string (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_ROLE,
                         gtk_window_get_role (GTK_WINDOW (window)));

  state = gdk_window_get_state (gtk_widget_get_window (GTK_WIDGET (window)));
  if (state & GDK_WINDOW_STATE_MAXIMIZED)
    g_key_file_set_boolean (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_MAXIMIZED, TRUE);
  if (state & GDK_WINDOW_STATE_FULLSCREEN)
    g_key_file_set_boolean (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_FULLSCREEN, TRUE);

  active_screen = terminal_window_get_active (window);
  tabs = terminal_window_list_screen_containers (window);

  tab_names_array = g_ptr_array_sized_new (g_list_length (tabs) + 1);

  for (lt = tabs; lt != NULL; lt = lt->next)
    {
      TerminalScreen *screen;
      char *tab_group;

      screen = terminal_screen_container_get_screen (TERMINAL_SCREEN_CONTAINER (lt->data));

      tab_group = g_strdup_printf ("Terminal%p", screen);
      g_ptr_array_add (tab_names_array, tab_group);

      terminal_screen_save_config (screen, key_file, tab_group);

      if (screen == active_screen)
        {
          int w, h, x, y;
          char *geometry;

          g_key_file_set_string (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_ACTIVE_TAB, tab_group);


          terminal_screen_get_size (screen, &w, &h);
          gtk_window_get_position (GTK_WINDOW (window), &x, &y);
          geometry = g_strdup_printf ("%dx%d+%d+%d", w, h, x, y);
          g_key_file_set_string (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_GEOMETRY, geometry);
          g_free (geometry);
        }
    }

  g_list_free (tabs);

  len = tab_names_array->len;
  g_ptr_array_add (tab_names_array, NULL);
  tab_names = (char **) g_ptr_array_free (tab_names_array, FALSE);
  g_key_file_set_string_list (key_file, group, TERMINAL_CONFIG_WINDOW_PROP_TABS, (const char * const *) tab_names, len);
  g_strfreev (tab_names);
}
