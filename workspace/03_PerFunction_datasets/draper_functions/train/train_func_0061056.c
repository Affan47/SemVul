mx_settings_get_property (GObject    *object,
                          guint       property_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
  guint uint_value;
  gchar *string_value;
  gboolean boolean_value;

  MxSettingsPrivate *priv = MX_SETTINGS (object)->priv;


  if (priv->provider)
    {
      switch (property_id)
        {
        case MX_SETTINGS_ICON_THEME:
        case MX_SETTINGS_FONT_NAME:
          if (_mx_settings_provider_get_setting (priv->provider, property_id,
                                                 &string_value))
            {
              g_value_set_string (value, string_value);
              return;
            }
          break;

        case MX_SETTINGS_LONG_PRESS_TIMEOUT:
          if (_mx_settings_provider_get_setting (priv->provider, property_id,
                                                 &uint_value))
            {
              g_value_set_uint (value, uint_value);
              return;
            }
          break;

        case MX_SETTINGS_SMALL_SCREEN:
          if (_mx_settings_provider_get_setting (priv->provider, property_id,
                                                 &boolean_value))
            {
              g_value_set_boolean (value, boolean_value);
              return;
            }
          break;

        case MX_SETTINGS_DRAG_THRESHOLD:
          if (_mx_settings_provider_get_setting (priv->provider, property_id,
                                                 &uint_value))
            {
              g_value_set_uint (value, uint_value);
              return;
            }
        }
    }


  switch (property_id)
    {
    case MX_SETTINGS_ICON_THEME:
      g_value_set_string (value, priv->icon_theme);
      break;

    case MX_SETTINGS_FONT_NAME:
      g_value_set_string (value, priv->font_name);
      break;

    case MX_SETTINGS_LONG_PRESS_TIMEOUT:
      g_value_set_uint (value, priv->long_press_timeout);
      break;

    case MX_SETTINGS_SMALL_SCREEN:
      g_value_set_boolean (value, priv->small_screen);
      break;

    case MX_SETTINGS_DRAG_THRESHOLD:
      g_value_set_uint (value, priv->drag_threshold);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
    }
}
