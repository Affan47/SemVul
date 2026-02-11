egg_tray_manager_unmanage (EggTrayManager *manager)
{
  Display *display;
  guint32 timestamp;
  GtkWidget *invisible;

  if (manager->invisible == NULL)
    return;

  invisible = manager->invisible;
  g_assert (GTK_IS_INVISIBLE (invisible));
  g_assert (GTK_WIDGET_REALIZED (invisible));
  g_assert (GDK_IS_WINDOW (invisible->window));

  display = GDK_WINDOW_XDISPLAY (invisible->window);

  if (XGetSelectionOwner (display, manager->selection_atom) ==
      GDK_WINDOW_XWINDOW (invisible->window))
    {
      timestamp = gdk_x11_get_server_time (invisible->window);
      XSetSelectionOwner (display, manager->selection_atom, None, timestamp);
    }

  gdk_window_remove_filter (invisible->window, egg_tray_manager_window_filter, manager);

  manager->invisible = NULL;
  gtk_widget_destroy (invisible);
  g_object_unref (G_OBJECT (invisible));
}
