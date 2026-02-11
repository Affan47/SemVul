on_rendering_control_last_change (GUPnPServiceProxy *rendering_control,
                                  const char        *variable_name,
                                  GValue            *value,
                                  gpointer           user_data)
{
       const char *last_change_xml;
       guint       volume;
       GError     *error;

       last_change_xml = g_value_get_string (value);
       error = NULL;

       if (gupnp_last_change_parser_parse_last_change (lc_parser,
                                                       0,
                                                       last_change_xml,
                                                       &error,
                                                       "Volume",
                                                       G_TYPE_UINT,
                                                       &volume,
                                                       NULL)) {
                       const char *udn;

                       udn = gupnp_service_info_get_udn
                                        (GUPNP_SERVICE_INFO
                                                (rendering_control));
                       set_volume (udn, volume);
       } else if (error) {
               g_warning ("%s\n", error->message);

               g_error_free (error);
       }
}
