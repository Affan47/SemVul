stat_server_push(void)
{
    unsigned int ip;

    if(global.stat_server_fd == INVALID_SOCKET)
    {

        if(!*global.stat_user || !*global.stat_pass || !*global.stat_server)
        {
            return;
        }

        global.stat_server_fd = make_tcp_connection(global.stat_server, global.stat_server_port, &ip);
        if(global.stat_server_fd != INVALID_SOCKET)
        {

            add_fd(global.stat_server_fd);
            set_write(global.stat_server_fd);
        }
        return;
    }

    snprintf(Buf, sizeof(Buf), "STATS %s %u %u 0 %.0f 0\r\n", global.report_name, global.usersHash->dbsize, global.fileLibCount, global.fileLibSize * 1024);

    if(WRITE(global.stat_server_fd, Buf, strlen(Buf)) == -1)
    {
        log_message_level( LOG_LEVEL_SERVER,  "stat_server_push: write: %s (%d)", strerror(N_ERRNO), N_ERRNO);
        CLOSE(global.stat_server_fd);
#if HAVE_POLL
        remove_fd(global.stat_server_fd);
#else
        FD_CLR(global.stat_server_fd, &global.read_fds);
        FD_CLR(global.stat_server_fd, &global.write_fds);
#endif
        global.stat_server_fd = INVALID_SOCKET;
    }
}
