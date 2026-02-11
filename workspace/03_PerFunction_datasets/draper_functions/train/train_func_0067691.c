get_peer(char *buf, socklen_t buflen)
{
#if !defined(HAVE_WIN32)
    if (peer_addr.sin_family == 0) {
        socklen_t salen = sizeof(peer_addr);
        int rval = (getpeername)(m_fd, (struct sockaddr *)&peer_addr, &salen);
        if (rval < 0) return rval;
    }
    if (!inet_ntop(peer_addr.sin_family, &peer_addr.sin_addr, buf, buflen))
        return -1;

    return 0;
#else
    return -1;
#endif
}
