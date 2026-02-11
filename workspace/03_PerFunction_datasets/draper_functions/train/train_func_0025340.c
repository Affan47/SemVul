na_tray_manager_set_colors (NaTrayManager *manager,
                            GdkColor      *fg,
                            GdkColor      *error,
                            GdkColor      *warning,
                            GdkColor      *success)
{
  g_return_if_fail (NA_IS_TRAY_MANAGER (manager));

  if (!gdk_color_equal (&manager->fg, fg) ||
      !gdk_color_equal (&manager->error, error) ||
      !gdk_color_equal (&manager->warning, warning) ||
      !gdk_color_equal (&manager->success, success))
    {
      manager->fg = *fg;
      manager->error = *error;
      manager->warning = *warning;
      manager->success = *success;

      na_tray_manager_set_colors_property (manager);
    }
}
