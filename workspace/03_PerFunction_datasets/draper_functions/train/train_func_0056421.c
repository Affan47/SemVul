ibus_registry_destroy (IBusRegistry *registry)
{
    ibus_registry_remove_all (registry);

    g_hash_table_destroy (registry->priv->monitor_table);
    registry->priv->monitor_table = NULL;

    if (registry->priv->monitor_timeout_id > 0) {
        g_source_remove (registry->priv->monitor_timeout_id);
        registry->priv->monitor_timeout_id = 0;
    }

    IBUS_OBJECT_CLASS (ibus_registry_parent_class)->
            destroy (IBUS_OBJECT (registry));
}
