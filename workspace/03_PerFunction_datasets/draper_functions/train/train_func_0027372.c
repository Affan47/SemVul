list_workspace (WnckWorkspace *space)
{
  WnckWindow *window;
  GList      *all_windows;
  GList      *l;
  GList      *space_windows;

  all_windows = wnck_screen_get_windows (wnck_workspace_get_screen (space));
  space_windows = NULL;

  for (l = all_windows; l; l = l->next)
    {
      window = WNCK_WINDOW (l->data);

      if (wnck_window_get_workspace (window) != NULL &&
          wnck_window_get_workspace (window) != space)
        continue;

      space_windows = g_list_prepend (space_windows, window);
    }

  space_windows = g_list_reverse (space_windows);

  list_windows (space_windows);

  g_list_free (space_windows);
}
