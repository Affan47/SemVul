wnck_selector_insert_window (WnckSelector *selector, WnckWindow *window)
{
  GtkWidget     *item;
  WnckScreen    *screen;
  WnckWorkspace *workspace;
  int            workspace_n;
  int            i;

  screen = wnck_selector_get_screen (selector);
  workspace = wnck_window_get_workspace (window);

  if (!workspace && !wnck_window_is_pinned (window))
    return;

  item = wnck_selector_create_window (selector, window);

  if (!workspace || workspace == wnck_screen_get_active_workspace (screen))
    {


      GList *l, *children;

      i = 0;

      children = gtk_container_get_children (GTK_CONTAINER (selector->priv->menu));
      for (l = children; l; l = l->next)
        {
          if (GTK_IS_SEPARATOR_MENU_ITEM (l->data))
            break;
          i++;
        }
      g_list_free (children);

      gtk_menu_shell_insert (GTK_MENU_SHELL (selector->priv->menu),
                             item, i);
    }
  else
    {
      workspace_n = wnck_workspace_get_number (workspace);

      if (workspace_n == wnck_screen_get_workspace_count (screen) - 1)

        gtk_menu_shell_append (GTK_MENU_SHELL (selector->priv->menu), item);
      else
        {

          GList *l, *children;

          i = 0;

          children = gtk_container_get_children (GTK_CONTAINER (selector->priv->menu));
          for (l = children; l; l = l->next)
            {
              int j;
              j = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (l->data),
                                                      "wnck-selector-workspace-n"));
              if (j - 1 == workspace_n + 1)
                break;
              i++;
            }
          g_list_free (children);

          gtk_menu_shell_insert (GTK_MENU_SHELL (selector->priv->menu),
                                 item, i);
        }
    }
}
