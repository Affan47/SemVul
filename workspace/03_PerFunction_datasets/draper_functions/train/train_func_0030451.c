ha_msg_dispatch(ll_cluster_t * cluster_conn, gpointer user_data)
{
    IPC_Channel *channel = NULL;

    crm_trace("Invoked");

    if (cluster_conn != NULL) {
        channel = cluster_conn->llc_ops->ipcchan(cluster_conn);
    }

    CRM_CHECK(cluster_conn != NULL, return FALSE);
    CRM_CHECK(channel != NULL, return FALSE);

    if (channel != NULL && IPC_ISRCONN(channel)) {
        if (cluster_conn->llc_ops->msgready(cluster_conn) == 0) {
            crm_trace("no message ready yet");
        }

        cluster_conn->llc_ops->rcvmsg(cluster_conn, 0);
    }

    if (channel == NULL || channel->ch_status != IPC_CONNECT) {
        crm_info("Lost connection to heartbeat service.");
        return FALSE;
    }

    return TRUE;
}
