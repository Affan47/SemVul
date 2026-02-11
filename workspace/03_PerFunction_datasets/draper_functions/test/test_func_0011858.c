ario_plugin_info_get_icon_name (ArioPluginInfo *info)
{
        g_return_val_if_fail (info != NULL, NULL);


        if (info->icon_name && ario_util_has_stock_icons (info->icon_name))
                return info->icon_name;
        else
                return "ario";
}
