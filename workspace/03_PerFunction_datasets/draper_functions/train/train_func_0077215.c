cc_connect(CyanChat* cc, const char* host, unsigned short port) {
    struct hostent* hp;
    struct sockaddr_in server;
    int sd = -1;

    if (cc == NULL || host == NULL) {
        return 0;
    }

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        return 0;
    }

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if ((hp = gethostbyname(host)) == NULL) {
        return 0;
    }

    memcpy((char*)&server.sin_addr, hp->h_addr, hp->h_length);

    if (connect(sd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        return 0;
    }

    cc->socket = sd;

    cc_send_welcome(cc);

    return 1;
}
