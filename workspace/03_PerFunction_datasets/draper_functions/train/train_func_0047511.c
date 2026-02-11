gwy_app_data_browser_get_keep_invisible(GwyContainer *data)
{
    GwyAppDataProxy *proxy;

    proxy = gwy_app_data_browser_get_proxy(gwy_app_get_data_browser(), data,
                                           FALSE);
    g_return_val_if_fail(proxy, FALSE);

    return proxy->keep_invisible;
}
