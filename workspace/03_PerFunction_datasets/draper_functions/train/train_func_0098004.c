cc_screen_panel_init (CcScreenPanel *self)
{
  GError     *error;
  GtkWidget  *widget;

  self->priv = SCREEN_PANEL_PRIVATE (self);

  self->priv->builder = gtk_builder_new ();

  error = NULL;
  gtk_builder_add_from_file (self->priv->builder,
                             GNOMECC_UI_DIR "/screen.ui",
                             &error);

  if (error != NULL)
    {
      g_warning ("Could not load interface file: %s", error->message);
      g_error_free (error);
      return;
    }

  self->priv->cancellable = g_cancellable_new ();


  g_dbus_proxy_new_for_bus (G_BUS_TYPE_SESSION,
                            G_DBUS_PROXY_FLAGS_NONE,
                            NULL,
                            "org.gnome.SettingsDaemon",
                            "/org/gnome/SettingsDaemon/Power",
                            "org.gnome.SettingsDaemon.Power.Screen",
                            self->priv->cancellable,
                            got_power_proxy_cb,
                            self);

  self->priv->lock_settings = g_settings_new ("org.gnome.desktop.screensaver");
  g_signal_connect (self->priv->lock_settings,
                    "changed",
                    G_CALLBACK (on_lock_settings_changed),
                    self);
  self->priv->gsd_settings = g_settings_new ("org.gnome.settings-daemon.plugins.power");
  self->priv->session_settings = g_settings_new ("org.gnome.desktop.session");
  self->priv->lockdown_settings = g_settings_new ("org.gnome.desktop.lockdown");
  g_signal_connect (self->priv->lockdown_settings,
                    "changed",
                    G_CALLBACK (on_lockdown_settings_changed),
                    self);


  widget = WID ("screen_auto_reduce_checkbutton");
  g_settings_bind (self->priv->gsd_settings,
                   "idle-dim",
                   widget, "active",
                   G_SETTINGS_BIND_DEFAULT);


  widget = WID ("screen_brightness_combobox");
  set_dpms_value_for_combo (GTK_COMBO_BOX (widget), self);
  g_signal_connect (widget, "changed",
                    G_CALLBACK (dpms_combo_changed_cb),
                    self);


  widget = WID ("screen_lock_on_switch");
  g_settings_bind (self->priv->lock_settings,
                   "lock-enabled",
                   widget, "active",
                   G_SETTINGS_BIND_DEFAULT);


  widget = WID ("screen_lock_combobox");
  set_lock_value_for_combo (GTK_COMBO_BOX (widget), self);
  g_signal_connect (widget, "changed",
                    G_CALLBACK (lock_combo_changed_cb),
                    self);

  widget = WID ("screen_lock_hbox");
  g_settings_bind (self->priv->lock_settings,
                   "lock-enabled",
                   widget, "sensitive",
                   G_SETTINGS_BIND_GET);

  widget = WID ("show_notifications_check");
  g_settings_bind (self->priv->lock_settings,
                   "show-notifications",
                   widget, "active",
                   G_SETTINGS_BIND_DEFAULT);
  if (!g_strcmp0(g_getenv("XDG_CURRENT_DESKTOP"), "Unity"))
    gtk_widget_hide (widget);

  update_lock_screen_sensitivity (self);


  widget = WID ("screen_lock_suspend_checkbutton");
  g_settings_bind (self->priv->lock_settings,
                   "ubuntu-lock-on-suspend",
                   widget, "active",
                   G_SETTINGS_BIND_DEFAULT);

  widget = WID ("screen_vbox");
  gtk_widget_reparent (widget, (GtkWidget *) self);
  g_object_set (self, "valign", GTK_ALIGN_START, NULL);
}
