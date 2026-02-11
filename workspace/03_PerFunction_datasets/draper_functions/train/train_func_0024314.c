ibus_config_set_value (IBusConfig   *config,
                       const gchar  *section,
                       const gchar  *name,
                       GVariant     *value)
{
    g_assert (IBUS_IS_CONFIG (config));
    g_assert (section != NULL);
    g_assert (name != NULL);
    g_assert (value != NULL);

    GError *error = NULL;
    GVariant *result;
    result = g_dbus_proxy_call_sync ((GDBusProxy *) config,
                                     "SetValue",
                                     g_variant_new ("(ssv)",
                                        section, name, value),
                                     G_DBUS_CALL_FLAGS_NONE,
                                     -1,
                                     NULL,
                                     &error
                                     );
    if (result == NULL) {
        g_warning ("%s.SetValue: %s", IBUS_INTERFACE_CONFIG, error->message);
        g_error_free (error);
        return FALSE;
    }
    g_variant_unref (result);
    return TRUE;
}
