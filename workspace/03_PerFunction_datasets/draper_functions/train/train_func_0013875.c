cc_info_panel_init (CcInfoPanel *self)
{
  GError *error = NULL;
  GtkWidget *widget;

  self->priv = INFO_PANEL_PRIVATE (self);

  self->priv->builder = gtk_builder_new ();

  self->priv->session_settings = g_settings_new (GNOME_SESSION_MANAGER_SCHEMA);
  self->priv->media_settings = g_settings_new (MEDIA_HANDLING_SCHEMA);

  self->priv->session_bus = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, NULL);

  g_assert (self->priv->session_bus);

  self->priv->pk_proxy = g_dbus_proxy_new_for_bus_sync (G_BUS_TYPE_SYSTEM,
                                                        G_DBUS_PROXY_FLAGS_NONE,
                                                        NULL,
                                                        "org.freedesktop.PackageKit",
                                                        "/org/freedesktop/PackageKit",
                                                        "org.freedesktop.PackageKit",
                                                        NULL,
                                                        NULL);
  if (self->priv->pk_proxy == NULL)
    {
      g_warning ("Unable to get PackageKit proxy object");
      self->priv->updates_state = PK_NOT_AVAILABLE;
    }
  else
    {
      GVariant *v;
      guint32 major, minor, micro;

      v = g_dbus_proxy_get_cached_property (self->priv->pk_proxy, "VersionMajor");
      g_variant_get (v, "u", &major);
      g_variant_unref (v);
      v = g_dbus_proxy_get_cached_property (self->priv->pk_proxy, "VersionMinor");
      g_variant_get (v, "u", &minor);
      g_variant_unref (v);
      v = g_dbus_proxy_get_cached_property (self->priv->pk_proxy, "VersionMicro");
      g_variant_get (v, "u", &micro);
      g_variant_unref (v);

      if (major != 0 || minor != 8)
        {
          g_warning ("PackageKit version %u.%u.%u not supported", major, minor, micro);
          g_clear_object (&self->priv->pk_proxy);
          self->priv->updates_state = PK_NOT_AVAILABLE;
        }
      else
        {
          g_signal_connect (self->priv->pk_proxy,
                            "g-signal",
                            G_CALLBACK (on_pk_signal),
                            self);
          refresh_updates (self);
        }
    }

  gtk_builder_add_from_file (self->priv->builder,
                             GNOMECC_UI_DIR "/info.ui",
                             &error);

  if (error != NULL)
    {
      g_warning ("Could not load interface file: %s", error->message);
      g_error_free (error);
      return;
    }

  self->priv->graphics_data = get_graphics_data ();

  widget = WID ("updates_button");
  g_signal_connect (widget, "clicked", G_CALLBACK (on_updates_button_clicked), self);

  info_panel_setup_selector (self);
  info_panel_setup_overview (self);
  info_panel_setup_default_apps (self);
  info_panel_setup_media (self);
  info_panel_setup_graphics (self);
}
