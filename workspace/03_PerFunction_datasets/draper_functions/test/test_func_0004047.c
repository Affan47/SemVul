_component_is_name_cb (BusComponent *component,
                       const gchar  *name)
{
    g_assert (BUS_IS_COMPONENT (component));
    g_assert (name);

    return g_strcmp0 (bus_component_get_name (component), name);
}
