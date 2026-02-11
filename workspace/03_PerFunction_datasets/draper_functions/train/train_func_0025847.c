dht_send(const void *buf, size_t len, int flags,
         const struct sockaddr *sa, int salen)
{
    int s;

    if(salen == 0)
        abort();

    if(node_blacklisted(sa, salen)) {
        debugf("Attempting to send to blacklisted node.\n");
        errno = EPERM;
        return -1;
    }

    if(sa->sa_family == AF_INET)
        s = dht_socket;
    else if(sa->sa_family == AF_INET6)
        s = dht_socket6;
    else
        s = -1;

    if(s < 0) {
        errno = EAFNOSUPPORT;
        return -1;
    }

    return sendto(s, buf, len, flags, sa, salen);
}
