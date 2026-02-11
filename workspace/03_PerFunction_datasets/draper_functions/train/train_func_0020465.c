vnc_connection_tls_initialize_anon_cred(void)
{
    gnutls_anon_client_credentials anon_cred;
    int ret;

    if ((ret = gnutls_anon_allocate_client_credentials(&anon_cred)) < 0) {
        VNC_DEBUG("Cannot allocate credentials %s", gnutls_strerror(ret));
        return NULL;
    }

    return anon_cred;
}
