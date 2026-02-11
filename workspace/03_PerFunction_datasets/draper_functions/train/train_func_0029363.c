bus_component_stop (BusComponent *component)
{
    g_assert (BUS_IS_COMPONENT (component));

    if (component->pid == 0)
        return TRUE;

    kill (component->pid, SIGTERM);
    return TRUE;
}
