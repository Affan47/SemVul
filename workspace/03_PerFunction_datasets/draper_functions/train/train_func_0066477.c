GetRemoteAddr(int in_fd) {
    struct sockaddr_in client_addr;
#ifdef HAVE_SOCKLEN_T
    socklen_t client_len;
#else
    int client_len;
#endif

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_len = sizeof(struct sockaddr_in);

    if (getsockname(in_fd, (struct sockaddr *) &client_addr, &client_len) < 0) {
        snprintf(errstr, STATUS_MAX, "TCP server unable to get sockname: %s",
				 strerror(errno));
        globalreg->messagebus->InjectMessage(errstr, MSGFLAG_ERROR);
		return "0.0.0.0";
    }

    return string(inet_ntoa(client_addr.sin_addr));
}
