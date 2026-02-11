socket_local_server_bind(int s, const char *name, int namespaceId)
{
    struct sockaddr_un addr;
    socklen_t alen;
    int n;
    int err;

    err = socket_make_sockaddr_un(name, namespaceId, &addr, &alen);

    if (err < 0) {
        return -1;
    }


#ifndef HAVE_LINUX_LOCAL_SOCKET_NAMESPACE
    if (1) {
#else
    if (namespaceId == ANDROID_SOCKET_NAMESPACE_RESERVED
        || namespaceId == ANDROID_SOCKET_NAMESPACE_FILESYSTEM) {
#endif

        unlink(addr.sun_path);
    }

    n = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));

    if(bind(s, (struct sockaddr *) &addr, alen) < 0) {
        return -1;
    }

    return s;

}
