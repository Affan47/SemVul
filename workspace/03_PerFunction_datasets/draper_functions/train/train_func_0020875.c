plugin_call_watches (PluginHandle * plugin)
{
    for (GList * node = plugin->watches; node; )
    {
        GList * next = node->next;
        PluginWatch * watch = node->data;

        if (! watch->func (plugin, watch->data))
        {
            g_free (watch);
            plugin->watches = g_list_delete_link (plugin->watches, node);
        }

        node = next;
    }
}
