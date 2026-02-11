bus_engine_proxy_property_activate (BusEngineProxy *engine,
                                    const gchar    *prop_name,
                                    guint           prop_state)
{
    g_assert (BUS_IS_ENGINE_PROXY (engine));
    g_assert (prop_name != NULL);

    g_dbus_proxy_call ((GDBusProxy *)engine,
                       "PropertyActivate",
                       g_variant_new ("(su)", prop_name, prop_state),
                       G_DBUS_CALL_FLAGS_NONE,
                       -1,
                       NULL,
                       NULL,
                       NULL);
}
