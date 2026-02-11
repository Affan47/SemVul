activate_panel (GnomeControlCenter *shell,
                const gchar        *id,
		const gchar       **argv,
                const gchar        *desktop_file,
                const gchar        *name,
                GIcon              *gicon)
{
  GnomeControlCenterPrivate *priv = shell->priv;
  GType panel_type = G_TYPE_INVALID;
  GList *panels, *l;
  GtkWidget *box;
  const gchar *icon_name;


  panels = g_io_extension_point_get_extensions (priv->extension_point);

  if (!desktop_file)
    return FALSE;
  if (!id)
    return FALSE;

  for (l = panels; l != NULL; l = l->next)
    {
      GIOExtension *extension;
      const gchar *name;

      extension = l->data;

      name = g_io_extension_get_name (extension);

      if (!g_strcmp0 (name, id))
        {
          panel_type = g_io_extension_get_type (extension);
          break;
        }
    }

  if (panel_type == G_TYPE_INVALID)
    {
	  GKeyFile *key_file;


	  key_file = g_key_file_new ();
	  if (g_key_file_load_from_file (key_file, desktop_file, G_KEY_FILE_NONE, NULL))
	    {
	      gchar *command;

	      command = g_key_file_get_string (key_file, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);
	      if (command && command[0])
	        {
		  g_spawn_command_line_async (command, NULL);
		  g_free (command);
		}
	    }

	  g_key_file_free (key_file);
      return FALSE;
    }


  priv->current_panel = g_object_new (panel_type, "shell", shell, "argv", argv, NULL);
  cc_shell_set_active_panel (CC_SHELL (shell), CC_PANEL (priv->current_panel));
  gtk_widget_show (priv->current_panel);

  gtk_lock_button_set_permission (GTK_LOCK_BUTTON (priv->lock_button),
                                  cc_panel_get_permission (CC_PANEL (priv->current_panel)));

  box = gtk_alignment_new (0, 0, 1, 1);
  gtk_alignment_set_padding (GTK_ALIGNMENT (box), 6, 6, 6, 6);

  gtk_container_add (GTK_CONTAINER (box), priv->current_panel);

  gtk_widget_set_name (box, id);
  notebook_add_page (priv->notebook, box);


  gtk_widget_show (box);
  notebook_select_page (priv->notebook, box);
  cc_shell_nav_bar_show_detail_button (CC_SHELL_NAV_BAR(shell->priv->nav_bar), name);


  icon_name = get_icon_name_from_g_icon (gicon);
  gtk_window_set_role (GTK_WINDOW (priv->window), id);
  gtk_window_set_title (GTK_WINDOW (priv->window), name);
  gtk_window_set_default_icon_name (icon_name);
  gtk_window_set_icon_name (GTK_WINDOW (priv->window), icon_name);

  priv->current_panel_box = box;

  return TRUE;
}
