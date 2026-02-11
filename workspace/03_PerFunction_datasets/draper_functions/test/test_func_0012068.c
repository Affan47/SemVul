start_plugins_one (void)
{
    plugin_system_init ();
    vfs_set_lookup_func (lookup_transport);

    for (int i = 0; i < PLUGIN_TYPE_GENERAL; i ++)
        start_plugins (i);
}
