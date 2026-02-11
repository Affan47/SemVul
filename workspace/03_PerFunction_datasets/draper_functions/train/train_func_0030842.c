bus_engine_proxy_get_property (BusEngineProxy *engine,
                               guint           prop_id,
                               GValue         *value,
                               GParamSpec     *pspec)
{
    switch (prop_id) {
    case PROP_ENGINE_DESC:
        g_value_set_object (value, bus_engine_proxy_get_desc (engine));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (engine, prop_id, pspec);
    }

}
