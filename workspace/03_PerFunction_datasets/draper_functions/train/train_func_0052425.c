notify_send(struct sockaddr *to, char *zone_name)
{
    int s;
    dns_sock_t *sock;

    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        plog_error(LOG_ERR, MODULE, "socket() failed");
        return -1;
    }

    if (connect(s, to, SALEN(to)) < 0) {
        plog_error(LOG_ERR, MODULE, "connect() failed");
        close(s);
        return -1;
    }

    if ((sock = dns_sock_udp_add(s, &SockPropNotify)) == NULL) {
        plog_error(LOG_ERR, MODULE, "dns_sock_add_udp() failed");
        close(s);
        return -1;
    }

    return notify_send_sock(sock, zone_name);
}
