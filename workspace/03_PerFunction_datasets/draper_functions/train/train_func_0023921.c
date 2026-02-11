_shell_set_active_panel_from_id (CcShell      *shell,
                                 const gchar  *start_id,
				 const gchar **argv,
                                 GError      **err)
{
  GtkTreeIter iter;
  gboolean iter_valid;
  gchar *name = NULL;
  gchar *desktop = NULL;
  GIcon *gicon = NULL;
  GnomeControlCenterPrivate *priv = GNOME_CONTROL_CENTER (shell)->priv;
  GtkWidget *old_panel;


  if (g_strcmp0 (priv->current_panel_id, start_id) == 0)
    {
      g_object_set (G_OBJECT (priv->current_panel), "argv", argv, NULL);
      return TRUE;
    }

  g_clear_pointer (&priv->current_panel_id, g_free);

  if (!g_strcmp0 (g_getenv ("XDG_CURRENT_DESKTOP"), "Unity") &&
      !g_strcmp0(start_id, "background"))
      start_id = "unity-appearance";


  _shell_remove_all_custom_widgets (priv);

  iter_valid = gtk_tree_model_get_iter_first (GTK_TREE_MODEL (priv->store),
                                              &iter);


  while (iter_valid)
    {
      gchar *id;

      gtk_tree_model_get (GTK_TREE_MODEL (priv->store), &iter,
                          COL_NAME, &name,
                          COL_DESKTOP_FILE, &desktop,
                          COL_GICON, &gicon,
                          COL_ID, &id,
                          -1);

      if (id && !strcmp (id, start_id))
        {
          g_free (id);
          break;
        }
      else
        {
          g_free (id);
          g_free (name);
          g_free (desktop);
	  if (gicon)
	    g_object_unref (gicon);

          name = NULL;
          id = NULL;
          desktop = NULL;
          gicon = NULL;
        }

      iter_valid = gtk_tree_model_iter_next (GTK_TREE_MODEL (priv->store),
                                             &iter);
    }

  if (!name)
    {
      g_warning ("Could not find settings panel \"%s\"", start_id);
    }
  else if (activate_panel (GNOME_CONTROL_CENTER (shell), start_id, argv, desktop,
                           name, gicon) == FALSE)
    {

      old_panel = priv->current_panel_box;
      priv->current_panel_box = NULL;
      notebook_select_page (priv->notebook, priv->scrolled_window);
      if (old_panel)
        notebook_remove_page (priv->notebook, old_panel);
    }
  else
    {
      priv->current_panel_id = g_strdup (start_id);
    }

  g_free (name);
  g_free (desktop);
  if (gicon)
    g_object_unref (gicon);

  return TRUE;
}
