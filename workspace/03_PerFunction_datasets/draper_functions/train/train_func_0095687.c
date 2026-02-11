setup_camera (CheeseWidget *widget)
{
  CheeseWidgetPrivate *priv = widget->priv;
  gchar *webcam_device = NULL;
  gint x_resolution;
  gint y_resolution;
  gdouble brightness;
  gdouble contrast;
  gdouble saturation;
  gdouble hue;

  g_settings_get (priv->settings, "photo-x-resolution", "i", &x_resolution);
  g_settings_get (priv->settings, "photo-y-resolution", "i", &y_resolution);
  g_settings_get (priv->settings, "camera",       "s", &webcam_device);
  g_settings_get (priv->settings, "brightness",   "d", &brightness);
  g_settings_get (priv->settings, "contrast",     "d", &contrast);
  g_settings_get (priv->settings, "saturation",   "d", &saturation);
  g_settings_get (priv->settings, "hue",          "d", &hue);

  gdk_threads_enter ();
  priv->webcam = cheese_camera_new (CLUTTER_TEXTURE (priv->texture),
                                    webcam_device,
                                    x_resolution,
                                    y_resolution);
  gdk_threads_leave ();

  g_free (webcam_device);

  cheese_camera_setup (priv->webcam, NULL, &priv->error);

  gdk_threads_enter ();

  gtk_spinner_stop (GTK_SPINNER (priv->spinner));

  if (priv->error != NULL)
  {
    cheese_widget_set_problem_page (CHEESE_WIDGET (widget), "error");
  }
  else
  {
    cheese_camera_set_balance_property (priv->webcam, "brightness", brightness);
    cheese_camera_set_balance_property (priv->webcam, "contrast", contrast);
    cheese_camera_set_balance_property (priv->webcam, "saturation", saturation);
    cheese_camera_set_balance_property (priv->webcam, "hue", hue);
    priv->state = CHEESE_WIDGET_STATE_READY;
    g_object_notify_by_pspec (G_OBJECT (widget), properties[PROP_STATE]);
    g_signal_connect (priv->webcam, "state-flags-changed",
                      G_CALLBACK (webcam_state_changed), widget);
    cheese_camera_play (priv->webcam);
    gtk_notebook_set_current_page (GTK_NOTEBOOK (widget), WEBCAM_PAGE);
  }

  gdk_threads_leave ();
}
