ario_plugin_info_is_configurable (ArioPluginInfo *info)
{
        ARIO_LOG_DBG ("Is '%s' configurable?", info->name);

        g_return_val_if_fail (info != NULL, FALSE);

        if (info->plugin == NULL || !info->active || !info->available)
                return FALSE;

        return ario_plugin_is_configurable (info->plugin);
}
