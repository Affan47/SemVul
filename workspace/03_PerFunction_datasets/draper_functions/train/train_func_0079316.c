create_socket(u_short port)
{
    struct sockaddr_in saddr;
    int s, on = 1;

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("creating socket");
        return -1;
    }

    (void)setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if (bind(s, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("binding socket");
        (void)close(s);
        return -1;
    }
    if (listen(s, 5) < 0) {
        perror("listening on socket");
        (void)close(s);
        return -1;
    }
    return s;
}
