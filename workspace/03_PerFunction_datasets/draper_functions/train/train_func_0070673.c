_start_listening(void)
{
    int i;
    for(i=0; i < global.server_sockets; i++) {
        if (sock_listen(global.serversock[i], ICE_LISTEN_QUEUE) == SOCK_ERROR)
            return 0;

        sock_set_blocking(global.serversock[i], 0);
    }

    return 1;
}
