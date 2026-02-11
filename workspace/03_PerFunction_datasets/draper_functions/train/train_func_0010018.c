genError(CommHndl conn_fd, Buffer * b, int status, char *title,
                     char *more)
{
    char head[1000];
    char server[] = "Server: sfcc indListener\r\n";
    char clength[] = "Content-Length: 0\r\n";
    char cclose[] = "Connection: close\r\n";
    char end[] = "\r\n";

    snprintf(head, sizeof(head), "%s %d %s\r\n", b->protocol, status, title);
    commWrite(conn_fd, head, strlen(head));
    if (more) {
        commWrite(conn_fd, more, strlen(more));
    }
    commWrite(conn_fd, server, strlen(server));
    commWrite(conn_fd, clength, strlen(clength));
    commWrite(conn_fd, cclose, strlen(cclose));

    commWrite(conn_fd, end, strlen(end));
    commFlush(conn_fd);
}
