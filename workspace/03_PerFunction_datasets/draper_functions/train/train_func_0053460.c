client_socket_init(uint16_t port)
{
    struct sockaddr_in address;
    int client_fd = -1;
    int i;


    for (i=0; i<3; i++) {
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr =  inet_addr("127.0.0.1");
        client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(client_fd, (struct sockaddr *)&address, sizeof(address)) == 0) break;
        perror("socket");
        SOCKET_CLOSE(client_fd);
        client_fd = -1;
        sleep(2);
    }

    return client_fd;
}
