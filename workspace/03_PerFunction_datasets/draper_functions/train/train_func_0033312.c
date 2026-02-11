dns_sock_send(dns_sock_buf_t *sbuf)
{
    dns_sock_t *sock = sbuf->sb_sock;

    if (sock->sock_prop->sp_func_send != NULL) {
        if (sock->sock_prop->sp_func_send(sock, sbuf) < 0)
            return -1;
    }

    return 0;
}
