action_group_setup_callbacks (GtkActionGroup *action_group,
                              GtkAccelGroup *accel_group,
                              GladeWindow *window)
{
  GList *l, *list = gtk_action_group_list_actions (action_group);

  for (l = list; l; l = g_list_next (l))
    {
      GtkAction *action = l->data;
      GSList *p, *proxies = gtk_action_get_proxies (action);
      gboolean is_recent = GTK_IS_RECENT_ACTION (action);


      gtk_accel_group_connect_by_path (accel_group,
                                       gtk_action_get_accel_path (action),
                                       gtk_action_get_accel_closure (action));

      for (p = proxies; p; p = g_slist_next (p))
        {
          GtkWidget *submenu, *proxy = p->data;

          gtk_activatable_sync_action_properties (GTK_ACTIVATABLE (proxy),
                                                  action);

          menu_item_connect (proxy, action, window);

          if (is_recent && GTK_IS_MENU_ITEM (proxy) &&
              (submenu = gtk_menu_item_get_submenu (GTK_MENU_ITEM (proxy))))
            recent_menu_setup_callbacks (submenu, window);
        }
    }

  g_list_free (list);
}
