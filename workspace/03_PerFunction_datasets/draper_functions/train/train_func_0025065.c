AcceptClient( SocketHandler &accept_socketT )
{
    addr_len = sizeof(my_s_addr);

    while ((accept_socketT.sock_fd = ::accept(sock_fd, (sockaddr *) &my_s_addr, (socklen_t *) &addr_len)) < 0)
    {
        if (errno == EINTR) continue;

        LogFile::ErrorMessage("accept() failed: %s\n", strerror(errno));

        return false;
    }


    accept_socketT.my_s_addr = my_s_addr;

    return true;
}
