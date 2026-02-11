_wnck_screen_change_workspace_name (WnckScreen *screen,
                                    int         number,
                                    const char *name)
{
  int n_spaces;
  char **names;
  int i;

  n_spaces = wnck_screen_get_workspace_count (screen);

  names = g_new0 (char*, n_spaces + 1);

  i = 0;
  while (i < n_spaces)
    {
      if (i == number)
        names[i] = (char*) name;
      else
        {
          WnckWorkspace *workspace;
          workspace = wnck_screen_get_workspace (screen, i);
          if (workspace)
            names[i] = (char*) wnck_workspace_get_name (workspace);
          else
            names[i] = (char*) "";
        }

      ++i;
    }

  _wnck_set_utf8_list (screen->priv->xroot,
                       _wnck_atom_get ("_NET_DESKTOP_NAMES"),
                       names);

  g_free (names);
}
