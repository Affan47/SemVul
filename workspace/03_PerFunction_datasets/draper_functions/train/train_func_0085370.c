remote_proxy_disconnected(void *userdata)
{
    remote_proxy_t *proxy = userdata;
    lrm_state_t *lrm_state = lrm_state_find(proxy->node_name);

    crm_trace("destroying %p", userdata);

    proxy->source = NULL;
    proxy->ipc = NULL;

    if (lrm_state && lrm_state->conn) {
        remote_proxy_notify_destroy(lrm_state->conn, proxy->session_id);
    }
    g_hash_table_remove(proxy_table, proxy->session_id);
}
