lrmd_send_xml(lrmd_t * lrmd, xmlNode * msg, int timeout, xmlNode ** reply)
{
    int rc = -1;
    lrmd_private_t *native = lrmd->private;

    switch (native->type) {
        case CRM_CLIENT_IPC:
            rc = crm_ipc_send(native->ipc, msg, crm_ipc_client_response, timeout, reply);
            break;
#ifdef HAVE_GNUTLS_GNUTLS_H
        case CRM_CLIENT_TLS:
            rc = lrmd_tls_send_recv(lrmd, msg, timeout, reply);
            break;
#endif
        default:
            crm_err("Unsupported connection type: %d", native->type);
    }

    return rc;
}
