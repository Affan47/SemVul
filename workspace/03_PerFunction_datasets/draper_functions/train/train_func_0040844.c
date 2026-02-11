on_updates_button_clicked (GtkWidget   *widget,
                           CcInfoPanel *self)
{
  GError *error;
  error = NULL;
  g_spawn_command_line_async ("update-manager", &error);
  if (error != NULL)
    {
      g_warning ("unable to launch Software Updates: %s", error->message);
      g_error_free (error);
    }
}
