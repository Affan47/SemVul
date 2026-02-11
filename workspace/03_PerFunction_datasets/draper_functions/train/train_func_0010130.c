trash_applet_factory (PanelApplet *applet,
                      const gchar *iid,
                      gpointer     data)
{
  gboolean retval = FALSE;

  if (!strcmp (iid, "TrashApplet"))
    {
      GtkActionGroup *action_group;
      gchar          *ui_path;

      g_set_application_name (_("Trash Applet"));

      gtk_window_set_default_icon_name ("user-trash");


      action_group = gtk_action_group_new ("Trash Applet Actions");
      gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
      gtk_action_group_add_actions (action_group,
				    trash_applet_menu_actions,
				    G_N_ELEMENTS (trash_applet_menu_actions),
				    applet);
      ui_path = g_build_filename (TRASH_MENU_UI_DIR, "trashapplet-menu.xml", NULL);
      panel_applet_setup_menu_from_file (applet, ui_path, action_group);
      g_free (ui_path);
      g_object_unref (action_group);

      gtk_widget_show (GTK_WIDGET (applet));

      retval = TRUE;
  }

  return retval;
}
