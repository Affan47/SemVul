na_tray_manager_set_orientation_property (NaTrayManager *manager)
{
#ifdef GDK_WINDOWING_X11
  GdkWindow  *window;
  GdkDisplay *display;
  Atom        orientation_atom;
  gulong      data[1];

  g_return_if_fail (manager->invisible != NULL);
  window = gtk_widget_get_window (manager->invisible);
  g_return_if_fail (window != NULL);

  display = gtk_widget_get_display (manager->invisible);
  orientation_atom = gdk_x11_get_xatom_by_name_for_display (display,
                                                            "_NET_SYSTEM_TRAY_ORIENTATION");

  data[0] = manager->orientation == GTK_ORIENTATION_HORIZONTAL ?
		SYSTEM_TRAY_ORIENTATION_HORZ :
		SYSTEM_TRAY_ORIENTATION_VERT;

  XChangeProperty (GDK_DISPLAY_XDISPLAY (display),
		   GDK_WINDOW_XID (window),
                   orientation_atom,
		   XA_CARDINAL, 32,
		   PropModeReplace,
		   (guchar *) &data, 1);
#endif
}
