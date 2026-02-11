NPP_New(NPMIMEType    mimetype,
        NPP           instance,
        uint16_t      mode,
        int16_t       argc,
        char        **argn,
        char        **argv,
        NPSavedData  *saved)
{

  PluginData *data;
  GError *error = NULL;

  g_debug ("plugin created");

  if (!check_origin_and_protocol (instance))
    return NPERR_GENERIC_ERROR;

  data = g_slice_new (PluginData);
  instance->pdata = data;

  data->proxy = g_dbus_proxy_new_for_bus_sync (G_BUS_TYPE_SESSION,
                                               G_DBUS_PROXY_FLAGS_NONE,
                                               NULL,
                                               "org.gnome.Shell",
                                               "/org/gnome/Shell",
                                               "org.gnome.Shell.Extensions",
                                               NULL,
                                               &error);
  if (!data->proxy)
    {

      if (error->domain != G_DBUS_ERROR ||
          error->code != G_DBUS_ERROR_NAME_HAS_NO_OWNER)
        {
          g_warning ("Failed to set up Shell proxy: %s", error->message);
        }
      g_clear_error (&error);
      return NPERR_GENERIC_ERROR;
    }

  g_debug ("plugin created successfully");

  return NPERR_NO_ERROR;
}
