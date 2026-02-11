gnac_ui_on_help_cb(GtkAction *action,
                   gpointer   user_data)
{
  gboolean ret;
  GError *error = NULL;

  ret = gtk_show_uri(gtk_widget_get_screen(gnac_ui_get_widget("main_window")),
      "ghelp:gnac", gtk_get_current_event_time(), &error);
  if (!ret && error) {
    g_printerr("%s: %s\n", _("Could not display help"), error->message);
    g_clear_error(&error);
  }
}
