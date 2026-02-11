gnc_plugin_page_get_plugin_name (GncPluginPage *plugin_page)
{
    GncPluginPageClass *klass;

    g_return_val_if_fail (GNC_IS_PLUGIN_PAGE (plugin_page), NULL);

    klass = GNC_PLUGIN_PAGE_GET_CLASS (plugin_page);
    g_return_val_if_fail (klass != NULL, NULL);

    return (klass->plugin_name);
}
