ibus_config_set_value_async (IBusConfig         *config,
                             const gchar        *section,
                             const gchar        *name,
                             GVariant           *value,
                             gint                timeout_ms,
                             GCancellable       *cancellable,
                             GAsyncReadyCallback callback,
                             gpointer            user_data)
{
    g_assert (IBUS_IS_CONFIG (config));
    g_assert (section != NULL);
    g_assert (name != NULL);
    g_assert (value != NULL);

    g_dbus_proxy_call ((GDBusProxy *) config,
                       "SetValue",
                       g_variant_new ("(ssv)",
                                      section, name, value),
                       G_DBUS_CALL_FLAGS_NONE,
                       timeout_ms,
                       cancellable,
                       callback,
                       user_data);
}
