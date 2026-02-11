cc_ua_panel_dispose (GObject *object)
{
  CcUaPanelPrivate *priv = CC_UA_PANEL (object)->priv;

  if (priv->shell_watch_id)
    {
      g_bus_unwatch_name (priv->shell_watch_id);
      priv->shell_watch_id = 0;
    }

  if (priv->builder)
    {
      g_object_unref (priv->builder);
      priv->builder = NULL;
    }

  if (priv->wm_settings)
    {
      g_object_unref (priv->wm_settings);
      priv->wm_settings = NULL;
    }

  if (priv->interface_settings)
    {
      g_object_unref (priv->interface_settings);
      priv->interface_settings = NULL;
    }

  if (priv->kb_settings)
    {
      g_object_unref (priv->kb_settings);
      priv->kb_settings = NULL;
    }

  if (priv->mouse_settings)
    {
      g_object_unref (priv->mouse_settings);
      priv->mouse_settings = NULL;
    }

  if (priv->application_settings)
    {
      g_object_unref (priv->application_settings);
      priv->application_settings = NULL;
    }

  if (priv->mediakeys_settings)
    {
      g_object_unref (priv->mediakeys_settings);
      priv->mediakeys_settings = NULL;
    }

  if (priv->zoom_options)
    {
      g_object_unref (priv->zoom_options);
      priv->zoom_options = NULL;
    }

  G_OBJECT_CLASS (cc_ua_panel_parent_class)->dispose (object);
}
