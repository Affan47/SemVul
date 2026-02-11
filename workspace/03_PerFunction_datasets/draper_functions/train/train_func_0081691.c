bus_component_destroy (BusComponent *component)
{
    if (component->pid != 0) {
        bus_component_stop (component);
        g_spawn_close_pid (component->pid);
        component->pid = 0;
    }

    if (component->child_source_id != 0) {
        g_source_remove (component->child_source_id);
        component->child_source_id = 0;
    }

    if (component->component != NULL) {
        g_object_unref (component->component);
        component->component = NULL;
    }

    IBUS_OBJECT_CLASS (bus_component_parent_class)->destroy (IBUS_OBJECT (component));
}
