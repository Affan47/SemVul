Close (SOCKET sock) {
    for(int i=0; i<sock_count; i++)
        if (sock_open[i].sock==sock)
            sock_open[i] = sock_open[--sock_count];
    if (!close_socket(sock))
        print_error("on closing a socket");
}
