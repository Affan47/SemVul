proxy_free(Proxy *proxy)
{
    gwy_object_unref(proxy->thumb);
    g_free(proxy->name);
    g_free(proxy);
}
