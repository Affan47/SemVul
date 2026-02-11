GetRemoteAddr(int in_fd) {
    struct sockaddr_un client_addr;
#ifdef HAVE_SOCKLEN_T
    socklen_t client_len;
#else
    int client_len;
#endif

    memset(&client_addr, 0, sizeof(client_addr));
    client_len = sizeof(client_addr);

    if (getsockname(in_fd, (struct sockaddr *) &client_addr, &client_len) < 0) {
        _MSG("Unix domain server unable to get sockname: " + string(strerror(errno)),
             MSGFLAG_ERROR);
        return "";
    }

    return client_addr.sun_path;
}
