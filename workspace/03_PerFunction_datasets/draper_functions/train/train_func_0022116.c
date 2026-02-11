frogr_controller_run_app (FrogrController *self, int argc, char **argv)
{
  FrogrControllerPrivate *priv = NULL;
  GtkApplication *app = NULL;
  gint status;

  g_return_val_if_fail(FROGR_IS_CONTROLLER (self), -1);

  priv = FROGR_CONTROLLER_GET_PRIVATE (self);

  if (priv->app_running)
    {
      DEBUG ("%s", "Application already running");
      return -1;
    }
  priv->app_running = TRUE;


  g_set_application_name(APP_SHORTNAME);
  app = gtk_application_new (APP_ID,
                             G_APPLICATION_NON_UNIQUE
                             | G_APPLICATION_HANDLES_OPEN);

  g_signal_connect (app, "startup", G_CALLBACK (_g_application_startup_cb), self);
  g_signal_connect (app, "activate", G_CALLBACK (_g_application_activate_cb), self);
  g_signal_connect (app, "shutdown", G_CALLBACK (_g_application_shutdown_cb), self);
  g_signal_connect (app, "open", G_CALLBACK (_g_application_open_files_cb), self);

  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
