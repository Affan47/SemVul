remote_proxy_remove_by_node(gpointer key, gpointer value, gpointer user_data)
{
    remote_proxy_t *proxy = value;
    const char *node_name = user_data;

    if (safe_str_eq(node_name, proxy->node_name)) {
        return TRUE;
    }

    return FALSE;
}
