anetSockName(int fd, char *ip, int *port) {
    struct sockaddr_in sa;
    socklen_t salen = sizeof(sa);

    if (getsockname(fd,(struct sockaddr*)&sa,&salen) == -1) {
        *port = 0;
        ip[0] = '?';
        ip[1] = '\0';
        return -1;
    }
    if (ip) strcpy(ip,inet_ntoa(sa.sin_addr));
    if (port) *port = ntohs(sa.sin_port);
    return 0;
}
