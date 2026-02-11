anjuta_recent_chooser_menu_insert_item (AnjutaRecentChooserMenu *menu,
                                     GtkWidget            *menuitem,
                                     gint                  position,
                                     gboolean              anjuta_project)
{
  AnjutaRecentChooserMenuPrivate *priv = menu->priv;
  gint real_position;

  if (priv->first_recent_item_pos == -1)
    {
      GList *children, *l;

      children = gtk_container_get_children (GTK_CONTAINER (menu));

      for (real_position = 0, l = children;
           l != NULL;
           real_position += 1, l = l->next)
        {
          GObject *child = l->data;
          gboolean is_placeholder = FALSE;

          is_placeholder =
            GPOINTER_TO_INT (g_object_get_data (child, "gtk-recent-menu-placeholder"));

          if (is_placeholder)
            break;
        }

      g_list_free (children);
      priv->first_recent_item_pos = real_position;
      priv->prj_pos = 0;
    }
  else
    real_position = priv->first_recent_item_pos;

  if (anjuta_project)
  {
    if (priv->prj_pos != 5)
    {
      gtk_menu_shell_insert (GTK_MENU_SHELL (menu), menuitem,
                             priv->prj_pos);
      priv->prj_pos++;
    }
  }
  else gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

  gtk_widget_show (menuitem);
}
