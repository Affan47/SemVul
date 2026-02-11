static_axes (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *button;
GtkWidget *label;
GdkColor color;

button = (GtkWidget *) g_object_get_data (G_OBJECT (window->window), "button_axes");
label = gtk_bin_get_child (GTK_BIN (button));

if (window->axes == FALSE)
  {
  window->axes = TRUE;
  gamgi_gtk_dialog_color (&color,
  GAMGI_GTK_ACTIVE_R, GAMGI_GTK_ACTIVE_G, GAMGI_GTK_ACTIVE_B);
  gamgi_gtk_dialog_color_fg (label, color);
  }
else
  {
  window->axes = FALSE;
  gamgi_gtk_statusbar_color (label, NULL, window);
  }


gamgi_gtk_statusbar_total (window);
}
