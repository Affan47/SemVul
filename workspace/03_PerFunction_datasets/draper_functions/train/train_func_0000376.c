cib_notify_send(xmlNode * xml)
{
    struct iovec *iov;
    struct cib_notification_s update;

    ssize_t rc = crm_ipc_prepare(0, xml, &iov);

    crm_trace("Notifying clients");

    if (rc > 0) {
        update.msg = xml;
        update.iov = iov;
        g_hash_table_foreach_remove(client_connections, cib_notify_send_one, &update);

    } else {
        crm_notice("Notification failed: %s (%d)", pcmk_strerror(rc), rc);
    }

    if (iov) {
        free(iov[0].iov_base);
        free(iov[1].iov_base);
        free(iov);
    }

    crm_trace("Notify complete");
}
