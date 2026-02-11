forward_connect(struct sockaddr *to, dns_tls_t *tls)
{
    int sock;

    if ((sock = forward_socket(to, tls)) < 0)
        return -1;

    if (connect(sock, to, SALEN(to)) < 0) {
        plog_error(LOG_ERR, MODULE, "connect() failed");
        close(sock);
        return -1;
    }

    return sock;
}
