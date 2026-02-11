general_unload (PluginHandle * plugin)
{
    GList * node = g_list_find_custom (loaded_general_plugins, plugin,
     (GCompareFunc) general_find_cb);
    if (node == NULL)
        return;

    AUDDBG ("Unloading %s.\n", plugin_get_name (plugin));
    LoadedGeneral * general = node->data;
    loaded_general_plugins = g_list_delete_link (loaded_general_plugins, node);

    if (general->widget != NULL)
    {
        AUDDBG ("Removing %s from interface.\n", plugin_get_name (plugin));
        interface_remove_plugin_widget (plugin, general->widget);
        g_return_if_fail (general->widget == NULL);
    }

    g_slice_free (LoadedGeneral, general);
}
