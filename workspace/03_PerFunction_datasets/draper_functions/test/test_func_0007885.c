crm_remote_send_raw(crm_remote_t * remote, const char *buf, size_t len)
{
    int rc = -ESOCKTNOSUPPORT;

    if (remote->tcp_socket) {
        rc = crm_send_plaintext(remote->tcp_socket, buf, len);
#ifdef HAVE_GNUTLS_GNUTLS_H

    } else if (remote->tls_session) {
        rc = crm_send_tls(remote->tls_session, buf, len);
#endif
    } else {
        crm_err("Unsupported connection type");
    }
    return rc;
}
