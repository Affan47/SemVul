ucftp_do_op(enum ucftp_op op, const char *dir, const char *file, struct ucftpconn *conn)
{
    int res;
    char *cmd;

    res = ucftp_open_conn(conn);
    if(res < 0)
        return res;

    res = ucftp_set_cwd(conn, dir);
    if(res < 0)
        return res;

    res = ucftp_open_dataconn(conn);
    if(res < 0)
        return res;

    cmd = av_stradd(NULL, ucftp_op_cmd[op], file, NULL);
    res = ucftp_command(conn, cmd);
    av_free(cmd);
    if(res >= 0 && res / 100 != 2)
        res = -EIO;

    if(res < 0) {
        return res;
    }

    return 0;
}
