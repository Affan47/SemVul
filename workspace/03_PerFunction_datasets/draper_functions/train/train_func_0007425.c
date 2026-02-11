visu_ui_dock_window_getCharacteristics(VisuUiDockWindow *dock, gchar **id,
					     gboolean *visibility,
					     gint *x, gint *y,
					     gint *width, gint *height)
{
  g_return_if_fail(dock);

  *id = dock->name;
  *visibility = dock->show;
  gtk_window_get_position(GTK_WINDOW(dock->window), x, y);
  gtk_window_get_size(GTK_WINDOW(dock->window), width, height);
}
