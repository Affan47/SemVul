sockaddr_in6_compare(ScmObj x, ScmObj y, int equalp)
{
    ScmSockAddrIn6 *xx = (ScmSockAddrIn6*)x;
    ScmSockAddrIn6 *yy = (ScmSockAddrIn6*)y;
    if (!equalp) Scm_Error("object %S and %S can't be ordered", x, y);

    if (xx->addrlen == yy->addrlen
        && xx->addr.sin6_family == yy->addr.sin6_family
        && xx->addr.sin6_port == yy->addr.sin6_port
        && (memcmp(&xx->addr.sin6_addr, &yy->addr.sin6_addr,
                   sizeof(xx->addr.sin6_addr)) == 0)) {
        return 0;
    } else {
        return -1;
    }
}
