gmpc_plugin_is_browser(gmpcPluginParent * plug)
{
    if (plug->new)
    {
        return GMPC_PLUGIN_IS_BROWSER_IFACE(plug->new);
    }
    return ((plug->old->plugin_type & GMPC_PLUGIN_PL_BROWSER) != 0);
}
