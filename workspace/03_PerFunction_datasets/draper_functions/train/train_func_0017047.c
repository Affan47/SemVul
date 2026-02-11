plugin_register (const char * path, int timestamp)
{
    PluginHandle * plugin = plugin_lookup (path);

    if (plugin)
    {
        AUDDBG ("Register plugin: %s\n", path);
        plugin->confirmed = TRUE;

        if (plugin->timestamp != timestamp)
        {
            AUDDBG ("Rescan plugin: %s\n", path);
            Plugin * header = plugin_load (path);
            if (! header || header->type != plugin->type)
                return;

            plugin->loaded = TRUE;
            plugin->header = header;
            plugin->timestamp = timestamp;

            plugin_get_info (plugin, FALSE);
        }
    }
    else
    {
        AUDDBG ("New plugin: %s\n", path);
        Plugin * header = plugin_load (path);
        if (! header)
            return;

        plugin = plugin_new (g_strdup (path), TRUE, TRUE, timestamp,
         header->type, header);

        plugin_get_info (plugin, TRUE);
    }
}
