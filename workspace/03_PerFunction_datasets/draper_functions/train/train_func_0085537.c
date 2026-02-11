send_orphand_message(pid_t parent,
                     pid_t child,
                     int action)
{
    ssize_t nw, nremaining, wtotal;
    char buf[12];
    uint32_t* bufp = (uint32_t*)buf;
    struct sockaddr_un saddr;
    char *sockpath;

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1) {
        perror(PROGNAME ": socket");
        return;
    }

    sockpath = getenv("ORPHAND_SOCKET");
    if (!sockpath) {
        sockpath = ORPHAND_DEFAULT_PATH;
    }

    saddr.sun_family = AF_UNIX;
    memcpy(saddr.sun_path, sockpath, strlen(sockpath)+1);

    bufp[0] = parent;
    bufp[1] = child;
    bufp[2] = action;

    if (connect(sock, (struct sockaddr*)&saddr, sizeof(saddr)) != 0) {
        fprintf(stderr, "%s: connect: %s\n", PROGNAME, strerror(errno));
        goto GT_END;
    }

    wtotal = 0;
    nremaining = 12;
    while (nremaining) {
        nw = send(sock, buf + wtotal, nremaining, 0);
        if (nw > 0) {
            nremaining -= nw;
            wtotal += nw;
        } else {
            if (nw == 0){
                fprintf(stderr, "%s: Remote closed connection\n", PROGNAME);
            } else {
                if (errno == EINTR) {
                    continue;
                }
                fprintf(stderr, "%s: send: %s\n", PROGNAME, strerror(errno));
            }
            break;
        }
    }

    GT_END:
    close(sock);
}
