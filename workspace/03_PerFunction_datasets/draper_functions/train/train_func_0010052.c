bus_input_context_property_changed (BusInputContext *context,
                                    const gchar     *property_name,
                                    GVariant        *value,
                                    GError         **error)
{
    if (context->connection == NULL)
        return TRUE;

    GVariantBuilder *builder = g_variant_builder_new (G_VARIANT_TYPE_ARRAY);
    g_variant_builder_add (builder, "{sv}", property_name, value);
    return bus_input_context_send_signal (context,
                                          "org.freedesktop.DBus.Properties",
                                          "PropertiesChanged",
                                          g_variant_new ("(sa{sv}as)",
                                                         "org.freedesktop.IBus",
                                                         builder,
                                                         NULL),
                                          error);
}
