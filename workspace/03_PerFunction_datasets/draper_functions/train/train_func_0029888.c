do_accept(int fd)
{
    struct sockaddr_in cliaddr;
    socklen_t addrlen = sizeof(cliaddr);

    int accpfd = accept(fd, (struct sockaddr*)&cliaddr, &addrlen);
    if (accpfd < 0) {
        return -1;
    }

    printf("accept new connection from: %s:%d\n",
            inet_ntoa(cliaddr.sin_addr),
            ntohs(cliaddr.sin_port));
    return accpfd;
}
