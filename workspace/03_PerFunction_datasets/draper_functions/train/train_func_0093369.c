ucftp_lookup_conn(struct ucftpfs *fs, const char *host,
                                           const char *user, const char *password)
{
    struct ucftpconn *conn;
    struct ucftpconn **cp;

    for(cp = &fs->conns; *cp != NULL; cp = &(*cp)->next) {
        conn = *cp;

        if(strcmp(conn->host, host) == 0 && strcmp(conn->user, user) == 0 &&
           strcmp(conn->password, password) == 0 && !conn->busy) {
            conn->busy = 1;
            return conn;
        }
    }

    AV_NEW(conn);

    conn->host = av_strdup(host);
    conn->user = av_strdup(user);
    conn->password = av_strdup(password);
    conn->busy = 1;
    conn->sock = -1;
    conn->sockfb = NULL;
    conn->next = NULL;
    conn->binary = -1;
    conn->cwd = av_strdup("");
    conn->ft_cancel_ok = 1;

    conn->root = ucftp_new_entry("/");
    ucftp_make_node(fs, conn->root, 0755 | AV_IFDIR);

    *cp = conn;

    return conn;
}
