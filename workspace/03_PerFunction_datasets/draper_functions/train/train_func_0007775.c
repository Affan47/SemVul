ftp_do_get(struct remgetparam *gp, const char *dir,
                      const char *file, struct ftpconn *conn)
{
    int res;
    int getsock;
    char *cmd;
    struct ftplocalfile *lf;

    res = ftp_open_conn(conn);
    if(res < 0)
        return res;

    res = ftp_set_binary(conn);
    if(res < 0)
        return res;

    res = ftp_set_cwd(conn, dir);
    if(res < 0)
        return res;

    res = ftp_open_dataconn(conn);
    if(res < 0)
        return res;

    getsock = res;
    cmd = av_stradd(NULL, "RETR ", file, NULL);
    res = ftp_command(conn, cmd);
    av_free(cmd);
    if(res >= 0 && res / 100 != 1)
        res = -EIO;

    if(res < 0) {
        close(getsock);
        return res;
    }

    AV_NEW_OBJ(lf, ftp_free_localfile);
    res = ftp_init_localfile(lf, getsock);
    if(res < 0) {
        av_unref_obj(lf);
        av_del_tmpfile(lf->tmpfile);
        return res;
    }

    lf->conn = conn;

    gp->data = lf;
    gp->localname = lf->tmpfile;

    return 0;
}
