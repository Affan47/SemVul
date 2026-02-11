terminal_app_set_property (GObject *object,
                            guint prop_id,
                            const GValue *value,
                            GParamSpec *pspec)
{
  TerminalApp *app = TERMINAL_APP (object);

  switch (prop_id)
    {
      case PROP_ENABLE_MENU_BAR_ACCEL:
        app->enable_menu_accels = g_value_get_boolean (value);
        gconf_client_set_bool (app->conf, ENABLE_MENU_BAR_ACCEL_KEY, app->enable_menu_accels, NULL);
        break;
      case PROP_ENABLE_MNEMONICS:
        app->enable_mnemonics = g_value_get_boolean (value);
        gconf_client_set_bool (app->conf, ENABLE_MNEMONICS_KEY, app->enable_mnemonics, NULL);
        break;
      case PROP_DEFAULT_PROFILE:
      case PROP_SYSTEM_FONT:

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
