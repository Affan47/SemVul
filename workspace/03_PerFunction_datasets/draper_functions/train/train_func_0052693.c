glade_gtk_menu_item_action_activate (GladeWidgetAdaptor * adaptor,
                                     GObject * object,
                                     const gchar * action_path)
{
  GObject *obj = NULL, *shell = NULL;
  GladeWidget *w = glade_widget_get_from_gobject (object);

  while ((w = glade_widget_get_parent (w)))
    {
      obj = glade_widget_get_object (w);
      if (GTK_IS_MENU_SHELL (obj))
        shell = obj;
    }

  if (strcmp (action_path, "launch_editor") == 0)
    {
      if (shell)
        object = shell;

      if (GTK_IS_MENU_BAR (object))
        glade_gtk_menu_shell_launch_editor (object, _("Edit Menu Bar"));
      else if (GTK_IS_MENU (object))
        glade_gtk_menu_shell_launch_editor (object, _("Edit Menu"));
    }
  else
    GWA_GET_CLASS (GTK_TYPE_CONTAINER)->action_activate (adaptor,
                                                         object, action_path);

  if (shell)
    gtk_menu_shell_deactivate (GTK_MENU_SHELL (shell));
}
